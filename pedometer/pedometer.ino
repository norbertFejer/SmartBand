#include "NineAxesMotion.h"
#include <Wire.h>
#include <SimpleTimer.h>

SimpleTimer timer;

NineAxesMotion motionSensor;
bool updateSensorData = true;         //Flag to update the sensor data. Default is true to perform the first read before the first stream
int count = 0;
byte flag = -1;
byte thresholdX = 26;
byte thresholdY = 30;
byte intervalCount = 0;
byte intervalCountThreshold = 3;

void setup() //This code is executed once
{
  //Peripheral Initialization
  Serial.begin(9600);           //Initialize the Serial Port to view information on the Serial Monitor
  I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor.

  //Sensor Initialization
  motionSensor.initSensor();          //The I2C Address can be changed here inside this function in the library
  motionSensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  motionSensor.setUpdateMode(MANUAL);  //The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions

  timer.setInterval(25, updateStepCounter);
  
  Serial.println("Arduino is ready...");
}

void updateStepCounter(){
  ++intervalCount;

    if(motionSensor.readGyroX() > thresholdX && motionSensor.readGyroY() > thresholdY && flag < 0){
      if(intervalCount >= intervalCountThreshold){ 
        ++count;
        flag = 1;
        intervalCount = 0;
        Serial.println(count);
      }
    }
    
    if(motionSensor.readGyroX() < -thresholdX && motionSensor.readGyroY() < -thresholdY && flag > 0){
      if(intervalCount >= intervalCountThreshold){ 
        ++count;
        flag = -1;
        intervalCount = 0;
        Serial.println(count);
      }
    }

    updateSensorData = true;
}

void loop()
{
  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    motionSensor.updateGyro();
    motionSensor.updateCalibStatus();  //Update the Calibration Status
    updateSensorData = false;
  }

  timer.run();
}
