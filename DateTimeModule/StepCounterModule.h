#ifndef STEPCOUNTERMODULE_H
#define STEPCOUNTERMODULE_H

#include <Arduino.h>
#include "NineAxesMotion.h"
#include "Wire.h"
#include <limits.h>
#include "DisplayModule.h"

class StepCounterModule
{

public:
	
	StepCounterModule(byte thresholdX, byte thresholdY, byte intervalCountThreshold, DisplayModule *displayModule) :
		mThresholdX(thresholdX),
		mThresholdY(thresholdY),
		mIntervalCountThreshold(intervalCountThreshold),
		mStepCount(0),
		mUpdateSensorData(true),
		mFlag(-1),
		mIntervalCount(0),
		mDispayModule(displayModule)
	{
	}

	~StepCounterModule()
	{
	}

	void runStepCounter();
	void initSensor();
	void updateSensor();
	void setStepCounter(int stepCount);


private:

	unsigned int mStepCount;
	NineAxesMotion mMotionSensor;
	bool mUpdateSensorData;         //Flag to update the sensor data. Default is true to perform the first read before the first stream
	byte mFlag;
	byte mThresholdX;
	byte mThresholdY;
	byte mIntervalCount;
	byte mIntervalCountThreshold;
	DisplayModule *mDispayModule;

};

#endif