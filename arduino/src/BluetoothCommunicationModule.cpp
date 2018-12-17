#include "BluetoothCommunicationModule.h"

void BluetoothCommunicationModule::runBluetoothCommunication()
{

	checkConnectionState();

	if (mSerialBtCommunication->available() > 0){
		String receivedStr = mSerialBtCommunication->readStringUntil('\n');
		mDataProcessModule->processData(receivedStr);
		Serial.println(receivedStr);
		mSerialBtCommunication->flush();
	}

	if (Serial.available()){
		mSerialBtCommunication->write(Serial.read());
	}

}


void BluetoothCommunicationModule::initBluetoothModule()
{

	mSerialBtCommunication->begin(9600);

}

void BluetoothCommunicationModule::checkConnectionState(){

	if(digitalRead(mStatePin) != mConnState){

	    mConnState = digitalRead(mStatePin);
	    mDataProcessModule->processData("i" + String(mConnState));

	    if(mConnState == 1){
	    	mDataProcessModule->sendStepCounterValueToClient();
	    }
	    
    }

}

void BluetoothCommunicationModule::sendData(String message){

	mSerialBtCommunication->print(message);

}

void BluetoothCommunicationModule::setShowNotification(bool state){
	delay(800);
	showNotification = state;
}
	
bool BluetoothCommunicationModule::getShowNotification(){
	return showNotification;
}

byte BluetoothCommunicationModule::getConnectionState(){
	return mConnState;
}
