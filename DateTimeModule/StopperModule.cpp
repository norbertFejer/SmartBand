#include "StopperModule.h"

void StopperModule::runStopper()
{
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