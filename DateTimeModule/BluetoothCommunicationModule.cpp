#include "BluetoothCommunicationModule.h"

void BluetoothCommunicationModule::runBluetoothCommunication()
{

	checkConnectionState();

	if (mSerialBtCommunication->available() > 0){
		String receivedStr = mSerialBtCommunication->readStringUntil('\n');
		mDataProcessModule->processData(receivedStr);
		Serial.println(receivedStr);
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
	    
    }

}

void BluetoothCommunicationModule::sendData(String message){

	mSerialBtCommunication->print(message);

}

void BluetoothCommunicationModule::setShowNotification(bool state){
	showNotification = state;
}
	
bool BluetoothCommunicationModule::getShowNotification(){
	return showNotification;
}

byte BluetoothCommunicationModule::getConnectionState(){
	return mConnState;
}
