#ifndef STOPPERMODULE_H
#define STOPPERMODULE_H

#include <Arduino.h>
#include "DisplayModule.h"

class StopperModule;

class StopperModule
{

public:

	StopperModule(DisplayModule *displayModule):
		mMillisecond(0),
		mSecond(0),
		mMinute(0),
		mDisplayModule(displayModule),
		mRunningState(false)
	{
		
	}

	~StopperModule()
	{
	}

	void runStopper();
	void resetStopper();
	void stopStopper();
	bool isRunning();
	int getMinute();
	int getSecond();
	int getMilliseconds();

private:

	int mMillisecond;
	int mSecond;
	int mMinute;
	bool mRunningState;
	DisplayModule *mDisplayModule;

};

#endif