#include "DataProcessModule.h"

void DataProcessModule::setBluetoothCommunicationModule(BluetoothCommunicationModule *bluetoothCommunicationModule){
	mBluetoothCommunicationModule = bluetoothCommunicationModule;
}

void DataProcessModule::setDisplayModule(DisplayModule *displayModule){
	mDisplayModule = displayModule;
}

void DataProcessModule::setDateTimeModule(DateTimeModule *dateTimeModule){
	mDateTimeModule = dateTimeModule;
}

void DataProcessModule::setStepCounterModule(StepCounterModule *stepCounterModule){
	mStepCounterModule = stepCounterModule;
}

void DataProcessModule::processData(String data){
	String code = data.substring(0, 1);
	char buf[2];
	code.toCharArray(buf, 2);

	switch((byte)buf[0]){
		case 115: //s
			s_case(data);
			break;
		case 116: //t
			t_case(data);
			break;
		case 100: //d
			d_case(data);
			break;
		case 109: //m
			m_case(data);
			break;
		case 112: //p
			p_case(data);
			break;
		case 105: //i
			i_case(data);
			break;
	}

}

void DataProcessModule::sendDataToBluetoothModule(String message){
	mBluetoothCommunicationModule->sendData(message);
}

void DataProcessModule::s_case(String data){
	int stepCount = data.substring(1, data.length()).toInt();
	//mStepCounterModule->setStepCounter(stepCount);
	Serial.println(stepCount);
}

void DataProcessModule::t_case(String data){
	String time = data.substring(1, data.length());
	//mDateTimeModule->setTime(time);
	Serial.println(time);
}

void DataProcessModule::d_case(String data){
	String date = data.substring(1, 5);
	//mDateTimeModule->setDate(date)
	Serial.println(date);

	int dayNum = data.substring(5, data.length()).toInt();
	//mDateTimeModule->setDayNumCount(dayNum);
	Serial.println(dayNum);
}

void DataProcessModule::m_case(String data){
	String message = data.substring(1, data.length());
	//mDisplayModule->printNotification(String message);
	Serial.println(message);
}

void DataProcessModule::p_case(String data){
	String message = data.substring(1, data.length());
	//mDisplayModule->printNotification(String message);
	Serial.println(message);
}

void DataProcessModule::i_case(String data){
	int connState = data.substring(1, data.length()).toInt();
	mDisplayModule->printConnectionState(connState);
	//Serial.println("i_case");
}