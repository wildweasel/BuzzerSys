#include "Buzzer.h"

struct Buzzers
{

private:

	  const static int numBuzzers = 12;

	  // Buzzer Constructor args are buttonPin, LED pin, LED (light) color
	  Buzzer buzzers[numBuzzers] = {
                Buzzer(53, A12, "purple"),
                Buzzer(51, A13, "blue"),
                Buzzer(49, A14, "green"),
                Buzzer(47, A15, "yellow"),
                Buzzer(45, A8, "orange"),
                Buzzer(41, A9, "red"),
                Buzzer(43, A10, "indigo"),
                Buzzer(39, A11, "turquoise"),
                Buzzer(37, A3, "chartreuse"),
                Buzzer(35, A4, "gold"),
                Buzzer(33, A5, "peach"),
                Buzzer(31, A6, "pink")              
               };

public:

  int getNumBuzzers(){
  	return numBuzzers;
  }
  
  String showColor(const int num){
  	return buzzers[num].getColor();
  }

  void initAll(){
    for(int i = 0; i < numBuzzers; i++){
      buzzers[i].init();
    }
  }

  int poll(const int num){
  	return buzzers[num].poll();
  }

  int pollAll(){
  	for(int i = 0; i < numBuzzers; i++){
  		if(buzzers[i].poll() == 1)
  			return i;
  	}
  	return -1;  	
  }

  void on(const int num){
    buzzers[num].lightOn();
  }
  
  void off(const int num){
    buzzers[num].lightOff();
  }

  void allOn(){
  	on(0);
	for(int i = 0; i < numBuzzers; i++){
     	on(i);      	
    }
  }

  void allOff(){
	for(int i = 0; i < numBuzzers; i++){
     	off(i);
    }
  }

  void lock(const int num){
  	buzzers[num].lock();
  }

  void unlock(const int num){
  	buzzers[num].unlock();
  }

  void unlockAll(){
  	for(int i = 0; i < numBuzzers; i++){
     	unlock(i);  
  	}
  }

  void cycleLED(int num){
  	buzzers[num].cycleLED();
  }

  void flashAll(const int timeMs = 400){
    allOn();
    delay(timeMs);  
    allOff();
  }

};