#include <Thread.h>
#include <LCD5110_Basic.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>
#include "NineAxesMotion.h"
#include <Wire.h>

LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];
SoftwareSerial serialBtCommunication(50, 51); // RX, TX
SimpleTimer timerTimer;
SimpleTimer stepCounterTimer;
const byte statePin = 4;

Thread timerThread = Thread();
Thread displayThread = Thread();
Thread stepCounterThread = Thread();

byte sec = 0;
byte hour = 0;
byte minute = 0;
String connStateStr = "Disconnected";
byte connState = 0;
unsigned int stepCount = 0;
byte month = 1;
byte day = 1;
byte dayNumCount = 0;
NineAxesMotion motionSensor;
bool updateSensorData = true;         //Flag to update the sensor data. Default is true to perform the first read before the first stream
byte flag = -1;
byte thresholdX = 32;
byte thresholdY = 36;
byte intervalCount = 0;
byte intervalCountThreshold = 4;

String dayArray[7] = { 
  "MON",
  "TUE",
  "WED",
  "THU",
  "FRI",
  "SAT",
  "SUN" 
  };

void timerDisplay() {
    if(sec == 60){
      ++minute;
      sec = 0;

      myGLCD.setFont(BigNumbers);
      
      if(minute == 60){
        ++hour;
        minute = 0;
      }
      if(hour == 24){
        hour = 0;
        ++day;
        ++dayNumCount;
        if(dayNumCount == 7){
          dayNumCount = 0;
        }
        byte dayNum = getMaxDay();
        if(day > dayNum){
          day = 0;
          ++month;
          if(month == 13){
            month = 0;
          }
        }
        printDisplayDatas();
      }
  
      myGLCD.setFont(BigNumbers);
      if(hour < 10){
        myGLCD.printNumI(0, LEFT, 24);
        myGLCD.printNumI(hour, LEFT + 14, 24);
      }
      else{
        myGLCD.printNumI(hour, LEFT, 24);
      }
  
      myGLCD.setFont(SmallFont);
      myGLCD.print(":", LEFT + 30, 34);
  
      myGLCD.setFont(BigNumbers);
      if(minute < 10){
        myGLCD.printNumI(0, LEFT + 36, 24);
        myGLCD.printNumI(minute, LEFT + 50, 24);
      }
      else{
        myGLCD.printNumI(minute, LEFT + 36, 24);
      }
    }

    ++sec;
}

void startTimer(){
  timerTimer.run();
}

int getMaxDay(){
  
  switch(month){
    case 1:
      return 31;
      break;
    case 2:
       return 28;
       break;
    case 3:
       return 31;
       break;
    case 4:
       return 30;
       break;
    case 5:
       return 31;
       break;
    case 6:
       return 30;
       break;
    case 7:
       return 31;
       break;
    case 8:
       return 31;
       break;
    case 9:
       return 30;
       break;
    case 10:
       return 31;
       break;
    case 11:
       return 30;
       break;
    case 12:
       return 31;
       break;
  }
  
}

void initDisplayTime(){
    myGLCD.setFont(BigNumbers);
    myGLCD.printNumI(0, LEFT, 24);
    myGLCD.printNumI(0, LEFT + 14, 24);
    myGLCD.setFont(SmallFont);
    myGLCD.print(":", LEFT + 30, 34);
    myGLCD.setFont(BigNumbers);
    myGLCD.printNumI(0, LEFT + 36, 24);
    myGLCD.printNumI(0, LEFT + 50, 24);
}

void printDate(){
  myGLCD.setFont(SmallFont);
  if(month < 10){
    myGLCD.printNumI(0, LEFT, 18);
    myGLCD.printNumI(month, LEFT + 6, 18);
  }
  else{
    myGLCD.printNumI(month, LEFT + 6, 18);
  }

  myGLCD.print(".", LEFT + 12, 18);

  if(day < 10){
    myGLCD.printNumI(0, LEFT + 18, 18);
    myGLCD.printNumI(day, LEFT + 24, 18);
  }
  else{
    myGLCD.printNumI(day, LEFT + 18, 18);
  }
}

void printDisplayDatas(){
  myGLCD.clrRow(0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print(connStateStr, LEFT, 0);

  myGLCD.print(dayArray[dayNumCount], RIGHT, 34);
  printDate();
}

void updateStepCounter(){
  
  ++intervalCount;
  myGLCD.setFont(SmallFont);
  
  if(motionSensor.readGyroX() > thresholdX && motionSensor.readGyroY() > thresholdY && flag < 0){
    if(intervalCount >= intervalCountThreshold){ 
      ++stepCount;
      flag = 1;
      intervalCount = 0;
      myGLCD.printNumI(stepCount, RIGHT, 18);
      serialBtCommunication.write(stepCount);
    }
  }
  
  if(motionSensor.readGyroX() < -thresholdX && motionSensor.readGyroY() < -thresholdY && flag > 0){
    if(intervalCount >= intervalCountThreshold){ 
      ++stepCount;
      flag = -1;
      intervalCount = 0;
      myGLCD.printNumI(stepCount, RIGHT, 18);
      serialBtCommunication.write(stepCount);
    }
  }
  
  updateSensorData = true;
}

void startStepCounter(){
  stepCounterTimer.run();
}

void setup(){
  Serial.begin(9600);
  pinMode(statePin, INPUT);  

  timerThread.onRun(startTimer);
  timerThread.setInterval(995);

  displayThread.onRun(printDisplayDatas);
  displayThread.setInterval(5);

  stepCounterThread.onRun(startStepCounter);
  stepCounterThread.setInterval(5);

  timerTimer.setInterval(5, timerDisplay);
  
  myGLCD.InitLCD();

  initDisplayTime();
  printDisplayDatas();
  myGLCD.printNumI(stepCount, RIGHT, 18);

  serialBtCommunication.begin(9600);

  I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor.

  //Sensor Initialization
  motionSensor.initSensor();          //The I2C Address can be changed here inside this function in the library
  motionSensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  motionSensor.setUpdateMode(MANUAL);  //The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions

  stepCounterTimer.setInterval(25, updateStepCounter);

  Serial.println("Arduino is started");
}

void loop(){
  // checks if thread should run
  if(timerThread.shouldRun()){
    timerThread.run();
  }

  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    motionSensor.updateGyro();
    motionSensor.updateCalibStatus();  //Update the Calibration Status
    updateSensorData = false;
  }

  if(stepCounterThread.shouldRun()){
    stepCounterThread.run();
  }

  if(digitalRead(statePin) != connState){
    connState = digitalRead(statePin);
    
    if(connState == 0){
      connStateStr = "Disconnected";
    }
    else{
      connStateStr = "Connected";
    }
    
    if(displayThread.shouldRun()){
      displayThread.run();
    }
  }

  if (serialBtCommunication.available())
    Serial.write(serialBtCommunication.read());
  if (Serial.available()){
    serialBtCommunication.write(Serial.read());
  }
  
}
