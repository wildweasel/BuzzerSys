#include "LED.h"

// Use this for LED testing, not the game

struct LEDs{

private:
  const static int numLEDs = 12;
  
  LED LEDs[numLEDs] = {
                LED(A12, "purple"),
                LED(A13, "blue"),
                LED(A14, "green"),
                LED(A15, "yellow"),
                LED(A8, "orange"),
                LED(A9, "red"),
                LED(A10, "indigo"),
                LED(A11, "turquoise"),
                LED(A3, "chartreuse"),
                LED(A4, "gold"),
                LED(A5, "peach"),
                LED(A6, "pink")              
               };

public:
  void initAll(){
    for(int i = 0; i < numLEDs; i++){
      LEDs[i].init();
    }
  }
           
  void off(){
    for(int i = 0; i < numLEDs; i++){
      LEDs[i].off();
    }
  }

  void on(const int num){
    LEDs[num].on();
  }
  
  void off(const int num){
    LEDs[num].off();
  }

  void cycleLED(const int num, const int timeMs = 1000){
    on(num);
    delay(timeMs);                   
    off(num);
  }
  
  void allOn(){
    for(int i = 0; i < numLEDs; i++){
     on(i);
    }
  }

  void allOff(){
    for(int i = 0; i < numLEDs; i++){
     off(i);
    }
  }
  
  void cycleAll(const int timeMs = 1000){
    for(int i = 0; i < numLEDs; i++)
     cycleLED(i, timeMs);
  }
};
