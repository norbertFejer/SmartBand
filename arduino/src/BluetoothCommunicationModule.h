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
		mDataProcessModule(dataProcessModule),
		showNotification(false)
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
	void setShowNotification(bool state);
	bool getShowNotification();
	byte getConnectionState();

private:

	SoftwareSerial *mSerialBtCommunication; // RX, TX	
	byte mStatePin;
	byte mConnState;
	DataProcessModule *mDataProcessModule;
	bool showNotification;

	void checkConnectionState();

};

#endif