#ifndef DATETIMEMODULE_H
#define DATETIMEMODULE_H

#include <Arduino.h>

class DateTimeModule
{

public:
	
	DateTimeModule() :
		mSec(0),
		mHour(0),
		mMinute(0),
		mMonth(1),
		mDay(1),
		mDayNumCount(0)
	{
	}

	~DateTimeModule()
	{
	}

	void runTimer();
	void setDate(String date);
	void setTime(String time);
	void setDayNumCount(byte num);
	short getDate();
	short getTime();
	byte getDayNumCount();
	String getDay();

private:

	byte mSec;
	byte mHour;
	byte mMinute;
	byte mMonth;
	byte mDay;
	byte mDayNumCount;
	String mDayArray[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };

	byte getMaxDayNum();

};

#endif