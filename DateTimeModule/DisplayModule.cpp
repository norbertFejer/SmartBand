#include "DisplayModule.h"

void DisplayModule::printTime(short time)
{
	if(mPageNumber == 0){

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
}

void DisplayModule::initDisplayModule()
{
	mGLCD->InitLCD();

	printTime(0);
	printDate(101);
	printDay("MON");
	printStepCounterValue(0);
	printConnectionState(0);

}

void DisplayModule::printDate(short date)
{
	if(mPageNumber == 0){

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
}

void DisplayModule::printDay(String day)
{
	if(mPageNumber == 0){

		mGLCD->setFont(SmallFont);
		mGLCD->print(day, RIGHT, 34);

	}
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
	mGLCD->clrRow(2, 42);
	mGLCD->setFont(SmallFont);
	mGLCD->printNumI(stepCount, RIGHT, 18);
}

void DisplayModule::printStopper(int min, int sec, int msec){

	mGLCD->setFont(BigNumbers);

	if(min < 10){

		mGLCD->printNumI(0, LEFT, 24);
		mGLCD->printNumI(min, LEFT + 14, 24);

	}
	else{

		mGLCD->printNumI(min, LEFT, 24);

	}

	mGLCD->setFont(SmallFont);
	mGLCD->print(":", LEFT + 30, 34);

	mGLCD->setFont(BigNumbers);
	if(sec < 10){

		mGLCD->printNumI(0, LEFT + 36, 24);
		mGLCD->printNumI(sec, LEFT + 50, 24);

	}
	else{

		mGLCD->printNumI(sec, LEFT + 36, 24);

	}

	mGLCD->setFont(SmallFont);
	if(msec < 10){

		mGLCD->printNumI(0, LEFT + 66, 36);
		mGLCD->printNumI(msec, LEFT + 72, 36);

	}
	else{

		mGLCD->printNumI(msec, LEFT + 66, 36);

	}
}

LCD5110* DisplayModule::getLCD(){
	return mGLCD;
}

void DisplayModule::setPageNumber(byte pageNum){
	mPageNumber = pageNum;
}

byte DisplayModule::getPageNumber(){
	return mPageNumber;
}

void DisplayModule::clearStopperDisplayArea(){
	mGLCD->clrRow(2, 0, 32);
	mGLCD->clrRow(3, 0);
	mGLCD->clrRow(4, 0);
	mGLCD->clrRow(5, 0);
	mGLCD->setFont(SmallFont);
	mGLCD->print("Timer:", LEFT, 18);
}

void DisplayModule::clearMainWindowArea(){
	mGLCD->clrRow(2, 0, 40);
	mGLCD->clrRow(3, 0);
	mGLCD->clrRow(4, 0);
	mGLCD->clrRow(5, 0);
	mGLCD->setFont(SmallFont);
}