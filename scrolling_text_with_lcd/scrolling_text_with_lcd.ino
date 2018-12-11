// LCD5110_ViewFont 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the included full font.
//
// This program requires a Nokia 5110 LCD module
// and Arduino 1.5.2 (or higher).
//
// It is assumed that the LCD module is connected to
// the following pins.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//

#include <LCD5110_Basic.h>

LCD5110 myGLCD(8,9,10,11,12);

String message = "N is calling you";
int i = 0;
int pos;

extern uint8_t SmallFont[];

void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  //Serial.begin(9600);
}

void loop()
{
  myGLCD.clrScr();
  myGLCD.print(message.substring(i,message.length()), LEFT, 0);
  int s = message.length() - i;
  if(s < 14 && s > -2){
    Serial.println(s);
    //Serial.println(pos);
    myGLCD.print(message.substring(0, pos), (14 - pos) * 6, 0);
    ++pos;
    if(pos == 15){
      pos = 0;
    }
  }
  ++i;
  if((i > message.length() && i % 15 == 0) || s < 0){
    i = 0;
  }
  delay(500);
}
