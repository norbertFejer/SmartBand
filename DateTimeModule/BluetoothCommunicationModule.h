#ifndef BLUETOOTHCOMMUNICATIONMODULE_H
#define BLUETOOTHCOMMUNICATIONMODULE_H

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DataProcessModule.h"

class DataProcessModule;

class BluetoothCommunicationModule
{

public:

	BluetoothCommunicationModule(byte RX, byte TX, byte statePin, DataProcessModule *dataProcessModule):
		mStatePin(statePin),
		mConnState(0),
		mDataProcessModule(dataProcessModule)
	{
		mSerialBtCommunication = new SoftwareSerial(RX, TX); //default 50, 51
	}

	BluetoothCommunicationModule()
	{
	}

	~BluetoothCommunicationModule()
	{
	}

	void initBluetoothModule();
	void runBluetoothCommunication();
	void sendData(String message);

private:

	SoftwareSerial *mSerialBtCommunication; // RX, TX	
	byte mStatePin;
	byte mConnState;
	DataProcessModule *mDataProcessModule;

	void checkConnectionState();

};

#endif