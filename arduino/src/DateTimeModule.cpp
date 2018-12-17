#include "DateTimeModule.h"

void DateTimeModule::runTimer()
{
	if (mSec == 60) {
		++mMinute;
		mSec = 0;

		if (mMinute == 60) {
			++mHour;
			mMinute = 0;
		}
		if (mHour == 24) {
			mHour = 0;
			++mDay;
			++mDayNumCount;
			if (mDayNumCount == 7) {
				mDayNumCount = 0;
			}
			byte dayNum = getMaxDayNum();
			if (mDay > dayNum) {
				mDay = 0;
				++mMonth;
				if (mMonth == 13) {
					mMonth = 0;
				}
			}
			mDisplayModule->printDate(mMonth * 100 + mDay);
			mDisplayModule->printDay(mDayArray[mDayNumCount]);
		}

		mDisplayModule->printTime(mHour * 100 + mMinute);
	}

	++mSec;
}

byte DateTimeModule::getMaxDayNum()
{

	switch (mMonth) {
		case 1:
			return 31;
			break;
		case 2:
			return 28;
			break;
		case 3:
			return 31;
			break;
		case 4:
			return 30;
			break;
		case 5:
			return 31;
			break;
		case 6:
			return 30;
			break;
		case 7:
			return 31;
			break;
		case 8:
			return 31;
			break;
		case 9:
			return 30;
			break;
		case 10:
			return 31;
			break;
		case 11:
			return 30;
			break;
		case 12:
			return 31;
			break;
		}

	return 0;
}

void DateTimeModule::setDate(String date)
{
	if(date.length() == 4){

		String month = date.substring(0, 2);
		if(month.toInt() > 0 && month.toInt() < 13){
			mMonth = month.toInt();
		}
		
		date = date.substring(2, 4);
		if(date.toInt() > 0 && date.toInt() <= getMaxDayNum()){
			mDay = date.toInt();
		}

		mDisplayModule->printDate(mMonth * 100 + mDay);

	}
}

void DateTimeModule::setTime(String time)
{
	if(time.length() == 4){
		String hour = time.substring(0, 2);
		if(hour.toInt() >= 0 && hour.toInt() < 23){
			mHour = hour.toInt();
		}
		time = time.substring(2, time.length());
		if(time.toInt() >= 0 && time.toInt() < 61){
			mMinute = time.toInt();
		}
		mSec = 0;
		
		mDisplayModule->printTime(mHour * 100 + mMinute);

	}
}

void DateTimeModule::setDayNumCount(byte num)
{
	if(num >= 0 && num < 7){
		mDayNumCount = num;
		mDisplayModule->printDay(getDay());
	}
}

short DateTimeModule::getDate()
{
	return mMonth * 100 + mDay;
}

short DateTimeModule::getTime()
{
	return mHour * 100 + mMinute;
}

byte DateTimeModule::getDayNumCount()
{
	return mDayNumCount;
}

String DateTimeModule::getDay()
{
	return mDayArray[mDayNumCount];
}