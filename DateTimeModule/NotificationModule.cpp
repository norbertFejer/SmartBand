#include "NotificationModule.h"

void NotificationModule::printNotification(){

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

void NotificationModule::setMessage(String message){
	mMessage = message;
	mStrIterator = 0;
	mStrPos = 0;
}