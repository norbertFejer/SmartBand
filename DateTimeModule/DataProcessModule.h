#ifndef DATAPROCESSMODULE_H
#define DATAPROCESSMODULE_H

#include <Arduino.h>
#include "BluetoothCommunicationModule.h"
#include "DisplayModule.h"
#include "DateTimeModule.h"
#include "StepCounterModule.h"
#include "NotificationModule.h"

class BluetoothCommunicationModule;

class DataProcessModule
{

public:

	DataProcessModule()
	{
	}

	~DataProcessModule()
	{
	}

	void setBluetoothCommunicationModule(BluetoothCommunicationModule *bluetoothCommunicationModule);
	void setDisplayModule(DisplayModule *displayModule);
	void setDateTimeModule(DateTimeModule *dateTimeModule);
	void setStepCounterModule(StepCounterModule *stepCounterModule);
	void setNotificationModule(NotificationModule *notificationModule);
	void processData(String data);
	void sendDataToBluetoothModule(String message);
	void s_case(String message);
	void t_case(String message);
	void d_case(String message);
	void m_case(String message);
	void p_case(String message);
	void i_case(String message);
	void n_case(String message);

private:

	BluetoothCommunicationModule *mBluetoothCommunicationModule;
	DisplayModule *mDisplayModule;
	DateTimeModule *mDateTimeModule;
	StepCounterModule *mStepCounterModule;
	NotificationModule *mNotificationModule;

};

#endif