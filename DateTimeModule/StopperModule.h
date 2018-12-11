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
		mDisplayModule(displayModule)
	{
		
	}

	~StopperModule()
	{
	}

	void runStopper();


private:

	int mMillisecond;
	int mSecond;
	int mMinute;
	DisplayModule *mDisplayModule;

};

#endif