#ifndef DISPLAYMODULE_H
#define DISPLAYMODULE_H

#include <Arduino.h>
#include <LCD5110_Basic.h>
#include "Thread.h"
#include "SimpleTimer.h"

extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];

class DisplayModule
{

public:

	DisplayModule(byte x0, byte x1, byte x2, byte x3, byte x4):
		mStrIterator(0),
		mStrPos(0)

	{
		mGLCD = new LCD5110(x0, x1, x2, x3, x4); //default 8, 9, 10, 11, 12
		mThread = Thread();
	}

	DisplayModule()
	{
	}

	~DisplayModule()
	{
	}

	void initDisplayModule();
	void printTime(short time);
	void printDate(short date);
	void printDay(String day);
	void printConnectionState(byte connState);
	void printStepCounterValue(int stepCount);
	void printNotification(String message);
	void printStopper(int min, int sec, int msec);

private:

	LCD5110 *mGLCD;
	int mStrIterator;
	int mStrPos;
	Thread mThread;
	SimpleTimer mTimer;
	String mMessage;

	void startTimer();
	void printMessage();

};

#endif