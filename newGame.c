#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#define RelayPin      	0
#define LedPin		24
#define LedTwo		26
#define LBPin		7
#define SERVO 		1 //GPIO18
#define BtnPin		4
#define ObstaclePin	3



int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

//	printf("linker LedPin : GPIO %d(wiringPi pin)\n",VoicePin); //when initialize wiring successfully,print message to screen
	
	wiringPiSetup();
	softPwmCreate(SERVO, 0, 200);
	pinMode(BtnPin, INPUT);

	pinMode(RelayPin, OUTPUT);
	pinMode(LedTwo, OUTPUT);
	pinMode(LedPin, OUTPUT);
	pinMode(LBPin, INPUT);
	int temp;
	
	while(1){
		if(0 == digitalRead(BtnPin)){
			softPwmWrite(SERVO, 25); //0 degrees
                	delay(1000);
		}
		else if (1 == digitalRead(BtnPin)) {
			 softPwmWrite(SERVO, 18); //90 degrees
                	delay(1000);
		}
		if(digitalRead(LBPin) == 0){
			digitalWrite(RelayPin, LOW);			
			delay(250);
			digitalWrite(RelayPin, HIGH);
			delay(250);
	
			digitalWrite(LedPin, LOW);
			delay(100);
			digitalWrite(LedPin, HIGH);
			delay(50);
	
			digitalWrite(LedTwo, LOW);
			delay(100);
			digitalWrite(LedTwo, HIGH);
			delay(50);
		}
		if(digitalRead(LBPin) == 1){
			digitalWrite(RelayPin, LOW);
			delay(25);
			digitalWrite(RelayPin, HIGH);
			delay(25);

			digitalWrite(LedPin, LOW);
			delay(25);
			digitalWrite(LedPin, HIGH);
			delay(25);

			digitalWrite(LedTwo, LOW);
			delay(25);
			digitalWrite(LedTwo, HIGH);
			delay(25);
		}
	}
	return 0;
}

