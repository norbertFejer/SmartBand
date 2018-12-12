#include "StepCounterModule.h"

void StepCounterModule::runStepCounter()
{

	++mIntervalCount;

	if(mMotionSensor.readGyroX() > mThresholdX && mMotionSensor.readGyroY() > mThresholdY && mFlag < 0){

		if(mIntervalCount >= mIntervalCountThreshold){ 

			++mStepCount;
			mFlag = 1;
			mIntervalCount = 0;
			mDispayModule->printStepCounterValue(mStepCount);
			mBtcModule->sendData(String(mStepCount));

		}

	}

	if(mMotionSensor.readGyroX() < -mThresholdX && mMotionSensor.readGyroY() < -mThresholdY && mFlag > 0){

		if(mIntervalCount >= mIntervalCountThreshold){ 

			++mStepCount;
			mFlag = -1;
			mIntervalCount = 0;
			mDispayModule->printStepCounterValue(mStepCount);
			mBtcModule->sendData(String(mStepCount));

		}

	}

	if(mStepCount == INT_MAX){
		mStepCount = 0;
	}

	mUpdateSensorData = true;
}

void StepCounterModule::initSensor(){

	I2C.begin();
	mMotionSensor.initSensor();          //The I2C Address can be changed here inside this function in the library
	mMotionSensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
	mMotionSensor.setUpdateMode(MANUAL);  //The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions

}

void StepCounterModule::updateSensor(){

	if (mUpdateSensorData)  //Keep the updating of data as a separate task
	{
		mMotionSensor.updateGyro();
		mMotionSensor.updateCalibStatus();  //Update the Calibration Status
		mUpdateSensorData = false;
	}

}

void StepCounterModule::setStepCounter(int stepCount){

	if(stepCount >= 0 && stepCount < INT_MAX){
		mStepCount = stepCount;
		mDispayModule->printStepCounterValue(mStepCount);
	}
	
}