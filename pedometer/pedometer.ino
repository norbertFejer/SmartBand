#include "NineAxesMotion.h"
#include <Wire.h>

NineAxesMotion mySensor;
unsigned long lastStreamTime = 0;
const int streamPeriod = 40;          //To stream at 50Hz without using additional timers (time period(ms) =1000/frequency(Hz))
bool updateSensorData = true;         //Flag to update the sensor data. Default is true to perform the first read before the first stream
int count = 0;
int flag = -1;
int thresholdX = 40;
int thresholdY = 40;
int thresholdZ = 0;
int intervalCount = 0;
int intervalCountThreshold = 3;

void setup() //This code is executed once
{
  //Peripheral Initialization
  Serial.begin(9600);           //Initialize the Serial Port to view information on the Serial Monitor
  I2C.begin();                    //Initialize I2C communication to the let the library communicate with the sensor.

  //Sensor Initialization
  mySensor.initSensor();          //The I2C Address can be changed here inside this function in the library
  mySensor.setOperationMode(OPERATION_MODE_NDOF);   //Can be configured to other operation modes as desired
  mySensor.setUpdateMode(MANUAL);  //The default is AUTO. Changing to MANUAL requires calling the relevant update functions prior to calling the read functions
  Serial.println("Arduino is ready...");
}

void loop()
{
  if (updateSensorData)  //Keep the updating of data as a separate task
  {
    mySensor.updateGyro();
    mySensor.updateCalibStatus();  //Update the Calibration Status
    updateSensorData = false;
  }

  if ((millis() - lastStreamTime) >= streamPeriod)
  {
    lastStreamTime = millis();
    
    ++intervalCount;

    //Serial.println(mySensor.readGyroZ());
    if(mySensor.readGyroX() > thresholdX && mySensor.readGyroY() > thresholdY && flag < 0){
      if(intervalCount >= intervalCountThreshold){ 
        ++count;
        flag = 1;
        intervalCount = 0;
        Serial.println(count);
      }
    }
    
    if(mySensor.readGyroX() < -thresholdX && mySensor.readGyroY() < -thresholdY && flag > 0){
      if(intervalCount >= intervalCountThreshold){ 
        ++count;
        flag = -1;
        intervalCount = 0;
        Serial.println(count);
      }
    }

    updateSensorData = true;
  }
}
