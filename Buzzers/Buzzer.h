#include "LED.h"

struct Buzzer
{

private:
	int buttonPin;
	LED led;
	bool locked;
	bool timeLocked;
	unsigned long lockTime;
	int lockDuration; 

public:

	Buzzer(const int buttonPin, const int LEDPin = -1, const String LEDcolor = "") : buttonPin(buttonPin), led(LEDPin, LEDcolor), locked(false){
	}

	String getColor(){
		return led.getColor();
	}

	void init(){
		pinMode(buttonPin, INPUT);
		// The teacher buzzer is not associated with an LED
		if(led.getColor() != "")
			led.init();
	}

	int poll(){
		if(timeLocked){
			if(millis() - lockTime < lockDuration)
				return -1;
			else{
				timeLocked = false;
			}
		}
		if(locked)
			return -1;
  		if(digitalRead(buttonPin) == HIGH)
    		return 1;
    	return 0;
	}

	void lock(){
		locked = true;
	}

	void unlock(){
		locked = false;
	}

	void timelock(const int duration = 1000){
		timeLocked = true;
		lockTime = millis();
		lockDuration = duration;
	}

	void lightOn(){
		led.on();
	}

	void lightOff(){
		led.off();
	}

  	void cycleLED(const int timeMs = 1000){
    	led.on();
    	delay(timeMs);                   
    	led.off();
  	}

};