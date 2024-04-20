#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define BeepPin 15
#define a 440
#define f 349
#define cH 523
#define eH 659

#define Trig 4
#define Echo 27

static volatile u_int64_t startTime;
static volatile u_int64_t endTime;

void recordPulseLength(){
	startTime = micros();
	while(digitalRead(Echo) == HIGH);
	endTime = micros();
}

int main(void){
    if(wiringPiSetup() == -1){ //when initialize wiring failed, print messageto screen
        printf("setup wiringPi failed !");
        return 1;
    }

    pinMode(BeepPin, OUTPUT);   //set GPIO0 output
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
 
    digitalWrite(Trig, LOW);
    delay(500);
  
    int pressed = 0;
    float now;
    float beginTime;
    float finishTime;
    float distance;
    while(1){
	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);
	now = micros();
	while(digitalRead(Echo) == LOW && micros() - now < 30000);
	recordPulseLength();
	beginTime = micros();
	while(digitalRead(Echo) == HIGH);
	finishTime = micros() - beginTime;
	distance = finishTime * 34300 / 2;
	
	printf("distance = %f \n", distance); //test

	if(distance > 111111){
		pressed = 1;
	}else{
		pressed = 0;
	}
        if(pressed == 1){
        	digitalWrite(BeepPin, LOW);
        	delay(100);
        	digitalWrite(BeepPin, HIGH);
        	delay(100);
		
		pressed = 0;
	}
    }

    return 0;
}
