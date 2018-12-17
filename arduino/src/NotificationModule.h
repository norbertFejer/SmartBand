#ifndef NOTIFICATIONMODULE_H
#define NOTIFICATIONMODULE_H

#include <Arduino.h>
#include <LCD5110_Basic.h>

extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];

class NotificationModule
{

public:

	NotificationModule(LCD5110 *lcd):
		mGLCD(lcd),
		mStrIterator(0),
		mStrPos(0)
	{
	}

	~NotificationModule()
	{
	}

	void printNotification();
	void setMessage(String message);

private:

	LCD5110 *mGLCD;
	int mStrIterator;
	int mStrPos;
	String mMessage;

};

#endif