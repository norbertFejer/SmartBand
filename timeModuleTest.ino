#include <BluetoothCommunicationModule.h>
#include <DisplayModule.h>
#include <DateTimeModule.h>
#include <StepCounterModule.h>
#include <DataProcessModule.h>
#include <StopperModule.h>
#include <NotificationModule.h>
#include <Thread.h>
#include <SimpleTimer.h>

DisplayModule displayModule(8, 9, 10, 11, 12);
DateTimeModule dateTimeModule(&displayModule);
DataProcessModule dataProcessModule;
BluetoothCommunicationModule btcModule(50, 51, 3, &dataProcessModule);
StepCounterModule stepCounterModule(32, 36, 4, &displayModule, &btcModule);
StopperModule stopperModule(&displayModule);
NotificationModule notificationModule(displayModule.getLCD());

Thread timeThread = Thread();
Thread stepCounterThread = Thread();
Thread notificationThread = Thread();
Thread btcThread = Thread();

SimpleTimer timeTimer;
SimpleTimer notificationTimer;

int pageBtnPin = 6;
int confirmBtnPin = 7;
int pageBtnValue = 1;
int confirmBtnValue = 1;

int pageNumber = 0;
bool confirmBtnPressed = false;
unsigned long confirmBtnTimer = 0;
bool isStopperRunnable = false;
bool resetStopper = false;

int confirmBtnState = 0;
  // 0 - unpressed
  // 1 - pressed

void startTimeTimer(){
  timeTimer.run();
}

void startNotificationTimer(){
  notificationTimer.run();
}

void setup() {
  Serial.begin(9600);

  //data process
  displayModule.initDisplayModule();
  btcModule.initBluetoothModule();
  dataProcessModule.setBluetoothCommunicationModule(&btcModule);
  dataProcessModule.setDisplayModule(&displayModule);
  dataProcessModule.setDateTimeModule(&dateTimeModule);
  dataProcessModule.setStepCounterModule(&stepCounterModule);
  dataProcessModule.setNotificationModule(&notificationModule);

  //timer
  timeThread.onRun(startTimeTimer);
  timeThread.setInterval(1);
  timeTimer.setInterval(1000, [&dateTimeModule](){ dateTimeModule.runTimer();} );

  //step counter
  stepCounterModule.initSensor();

  stepCounterThread.onRun([&stepCounterModule](){ stepCounterModule.runStepCounter();} );
  stepCounterThread.setInterval(5);

  //notification 
  notificationThread.onRun(startNotificationTimer);
  notificationThread.setInterval(1);

  notificationTimer.setInterval(500, [&notificationModule](){ notificationModule.printNotification();} );

  //bluetooth communication thread
  btcThread.onRun([&btcModule](){ btcModule.runBluetoothCommunication();});
  btcThread.setInterval(1);

  //setting pushbuttons
  pinMode(pageBtnPin, INPUT_PULLUP);
  pinMode(confirmBtnPin, INPUT_PULLUP);
  
}

void loop() {
  //---------------
  
  if(timeThread.shouldRun()){
    timeThread.run();
  }
  
  //---------------
  
  if(btcModule.getShowNotification()){
    
    if(notificationThread.shouldRun()){
      notificationThread.run();
    }
     
  }
  
  //---------------
  
  stepCounterModule.updateSensor();
  
  //---------------
  
  if(stepCounterThread.shouldRun()){
    stepCounterThread.run();
  }
  
  //---------------
  
  if(btcThread.shouldRun()){
    btcThread.run();
    
  }
  //---------------
  
  int actualPageBtnValue = digitalRead(pageBtnPin);
  if(actualPageBtnValue != pageBtnValue && pageBtnValue == 1){
    ++pageNumber;
    if(pageNumber == 2){
      pageNumber = 0;
    }
    
    displayModule.setPageNumber(pageNumber);
    pageBtnValue = actualPageBtnValue;
    
    if(pageNumber == 0){
      displayModule.clearMainWindowArea();
      displayModule.printDate(dateTimeModule.getDate());
      displayModule.printDay(dateTimeModule.getDay());
      displayModule.printTime(dateTimeModule.getTime());
    }
    else{
      displayModule.clearStopperDisplayArea();
      stopperModule.resetStopper();
      displayModule.printStopper(0,0,0);
    }
  }
  
  if(actualPageBtnValue == 1){
    pageBtnValue = 1;
  }
  
  //---------------
  
  int actualConfirmBtnValue = digitalRead(confirmBtnPin);
  if(actualConfirmBtnValue == 0 && confirmBtnPressed == false){
    confirmBtnTimer = millis();
    confirmBtnPressed = true;
  }
  if(actualConfirmBtnValue != confirmBtnValue && confirmBtnValue == 0){
    if(millis() - confirmBtnTimer > 250){
      resetStopper = true;
      Serial.println("long pressed");
    }
    else{
      confirmBtnState = 1;
      isStopperRunnable = !isStopperRunnable;
      Serial.println("pressed");
    }
    confirmBtnPressed = false;
    confirmBtnTimer = 0;
  }
  confirmBtnValue = actualConfirmBtnValue;

  //---------------

  if(pageNumber == 1){
    if(resetStopper){
     stopperModule.resetStopper();
     resetStopper = false;
     displayModule.printStopper(0,0,0);
     isStopperRunnable = false;
    }
    if(isStopperRunnable){
      stopperModule.runStopper();
    }
  }
}
