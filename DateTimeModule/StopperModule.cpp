#include "StopperModule.h"

void StopperModule::runStopper()
{
	mRunningState = true;
	++mMillisecond;
	if(mMillisecond == 60){
		mMillisecond = 0;
		++mSecond;
		if(mSecond == 60){
			mSecond = 0;
			++mMinute;
			if(mMinute == 60){
				mMinute = 0;
			}
		}
	}

	//Serial.println(String(mMinute) + ":" + mSecond + ":" + String(mMillisecond));
	mDisplayModule->printStopper(mMinute, mSecond, mMillisecond);
	delay(10);
}

void StopperModule::resetStopper(){
	mMillisecond = 0;
	mSecond = 0;
	mMinute = 0;
}

bool StopperModule::isRunning(){
	return mRunningState;
}

void StopperModule::stopStopper(){
	mRunningState = false;
}

int StopperModule::getMinute(){
	return mMinute;
}

int StopperModule::getSecond(){
	return mSecond;
}

int StopperModule::getMilliseconds(){
	return mMillisecond;
}