#include <BluetoothCommunicationModule.h>
#include <DisplayModule.h>
#include <DateTimeModule.h>
#include <StepCounterModule.h>
#include <DataProcessModule.h>
#include <StopperModule.h>
#include <Thread.h>
#include <SimpleTimer.h>

DisplayModule displayModule(8, 9, 10, 11, 12);
DateTimeModule dateTimeModule(&displayModule);
StepCounterModule stepCounterModule(32, 36, 4, &displayModule);
DataProcessModule dataProcessModule;
BluetoothCommunicationModule btcModule(50, 51, 4, &dataProcessModule);
StopperModule stopperModule(&displayModule);

Thread timeThread = Thread();
Thread stepCounterThread = Thread();

SimpleTimer timeTimer;

void startTimeTimer(){
  timeTimer.run();
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

  //timer
  timeThread.onRun(startTimeTimer);
  timeThread.setInterval(5);
  //timeTimer.setInterval(25, [&btModule](){ btModule.runBluetoothCommunication();} );
  timeTimer.setInterval(10, [&dateTimeModule](){ dateTimeModule.runTimer();} );

  //step counter
  stepCounterModule.initSensor();

  stepCounterThread.onRun([&stepCounterModule](){ stepCounterModule.runStepCounter();} );
  stepCounterThread.setInterval(5);
}

void loop() {

  if(timeThread.shouldRun()){
    timeThread.run();
  }

  stepCounterModule.updateSensor();

  if(stepCounterThread.shouldRun()){
    stepCounterThread.run();
  }
  
  btcModule.runBluetoothCommunication();
}
