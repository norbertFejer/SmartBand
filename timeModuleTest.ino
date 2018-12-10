#include <BluetoothCommunicationModule.h>
#include <DisplayModule.h>
#include <DateTimeModule.h>
#include <StepCounterModule.h>
#include <DataProcessModule.h>

DisplayModule displayModule(8, 9, 10, 11, 12);
DateTimeModule dateTimeModule;
StepCounterModule stepCounterModule(32, 36, 4);
DataProcessModule dataProcessModule;
BluetoothCommunicationModule btcModule(50, 51, 4, &dataProcessModule);

void setup() {
  Serial.begin(9600);

  displayModule.initDisplayModule();
  btcModule.initBluetoothModule();
  dataProcessModule.setBluetoothCommunicationModule(&btcModule);
  dataProcessModule.setDisplayModule(&displayModule);

 // timerTimer.setInterval(25, [&btModule](){ btModule.runBluetoothCommunication();} );
}

void loop() {
  
  btcModule.runBluetoothCommunication();
  //dataProcessModule.sendDataToBluetoothModule("first send");
  //delay(500);
}
