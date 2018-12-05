#include <SimpleTimer.h>
#include <LCD5110_Basic.h>

LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t BigNumbers[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];

int sec = 0;

int hour = 0;
int minute = 0;

SimpleTimer timer;

void timerDisplay() {
  
    if(sec == 60){
      ++minute;
      sec = 0;

      myGLCD.clrScr();
      myGLCD.setFont(BigNumbers);
      
      if(minute == 60){
        ++hour;
        minute = 0;
      }
      if(hour == 25){
        hour = 0;
      }
  
      myGLCD.setFont(BigNumbers);
      if(hour < 10){
        myGLCD.printNumI(0, LEFT, 24);
        myGLCD.printNumI(hour, LEFT + 14, 24);
      }
      else{
        myGLCD.printNumI(23, LEFT, 24);
      }
  
      myGLCD.setFont(SmallFont);
      myGLCD.print(":", LEFT + 30, 34);
  
      myGLCD.setFont(BigNumbers);
      if(minute < 10){
        myGLCD.printNumI(0, LEFT + 36, 24);
        myGLCD.printNumI(minute, LEFT + 50, 24);
      }
      else{
        myGLCD.printNumI(minute, LEFT + 36, 24);
      }
      
    }
    
    ++sec;
}

void initDisplayTime(){
    myGLCD.setFont(BigNumbers);
    myGLCD.printNumI(0, LEFT, 24);
    myGLCD.printNumI(0, LEFT + 14, 24);
    myGLCD.setFont(SmallFont);
    myGLCD.print(":", LEFT + 30, 34);
    myGLCD.setFont(BigNumbers);
    myGLCD.printNumI(0, LEFT + 36, 24);
    myGLCD.printNumI(0, LEFT + 50, 24);
}

void setup() {
    timer.setInterval(1000, timerDisplay);
    myGLCD.InitLCD();

    initDisplayTime();
}

void loop() {
    timer.run();
}
