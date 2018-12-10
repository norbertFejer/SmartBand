#include "DisplayModule.h"

void DisplayModule::printTime(short time)
{
	short hour = time / 100;
	short minute = time % 100;

	mGLCD->setFont(BigNumbers);

	if(hour < 10){

		mGLCD->printNumI(0, LEFT, 24);
		mGLCD->printNumI(hour, LEFT + 14, 24);

	}
	else{

		mGLCD->printNumI(hour, LEFT, 24);

	}

	mGLCD->setFont(SmallFont);
	mGLCD->print(":", LEFT + 30, 34);

	mGLCD->setFont(BigNumbers);

	if(minute < 10){

		mGLCD->printNumI(0, LEFT + 36, 24);
		mGLCD->printNumI(minute, LEFT + 50, 24);

	}
	else{

		mGLCD->printNumI(minute, LEFT + 36, 24);

	}
}

void DisplayModule::initDisplayModule()
{
	mGLCD->InitLCD();

	//mThread.onRun( [this](){ startTimer(); } );
  	//mThread.setInterval(5);
  	//mTimer.setInterval(500, this { btModule.runBluetoothCommunication();} );
}

void DisplayModule::printDate(short date)
{
	short month = date / 100;
	short day = date % 100;
	mGLCD->setFont(SmallFont);

	if(month < 10){

		mGLCD->printNumI(0, LEFT, 18);
		mGLCD->printNumI(month, LEFT + 6, 18);

	}
	else{

		mGLCD->printNumI(month, LEFT, 18);

	}

	mGLCD->print(".", LEFT + 12, 18);

	if(day < 10){

		mGLCD->printNumI(0, LEFT + 18, 18);
		mGLCD->printNumI(day, LEFT + 24, 18);

	}
	else{

		mGLCD->printNumI(day, LEFT + 18, 18);

	}
}

void DisplayModule::printDay(String day)
{
	mGLCD->setFont(SmallFont);
	mGLCD->print(day, RIGHT, 34);
}

void DisplayModule::printConnectionState(byte connState)
{
	mGLCD->setFont(SmallFont);
	mGLCD->clrRow(0, 0);
	if(connState == 0){
		mGLCD->print("Disconnected", LEFT, 0);
	}
	else{
		mGLCD->print("Connected", LEFT, 0);
	}
}

void DisplayModule::printStepCounterValue(int stepCount){
	mGLCD->setFont(SmallFont);
	mGLCD->printNumI(stepCount, RIGHT, 18);
}

void DisplayModule::printMessage(){

	mGLCD->setFont(SmallFont);
	mGLCD->clrRow(0, 0);
	mGLCD->print(mMessage.substring(mStrIterator, mMessage.length()), LEFT, 0);

	int tmpPos = mMessage.length() - mStrIterator;

	if(tmpPos < 14 && tmpPos > -2){

		mGLCD->print(mMessage.substring(0, mStrPos), (14 - mStrPos) * 6, 0);
		++mStrPos;

		if(mStrPos == 15){
		  mStrPos = 0;
		}

	}

	++mStrIterator;

	if((mStrIterator > mMessage.length() && mStrIterator % 15 == 0) || tmpPos < 0){

		mStrIterator = 0;

	}

}

void DisplayModule::printNotification(String message){
	mMessage = message;
}

void DisplayModule::startTimer(){
	mTimer.run();
}