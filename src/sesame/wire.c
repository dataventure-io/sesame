/*
	wire.c

	Single-purpose wrapper of the Wiring PI library.  
*/
#include <wiringPi.h>
#include "wire.h"


/*
	Send a one-shot signal to pin BCM 23
*/
void wireOneShot()
{
	wiringPiSetup();

	pinMode(WIRING_PI_PIN, OUTPUT);

	digitalWrite(WIRING_PI_PIN, HIGH);  // On
	delay(1000); // ms
	digitalWrite(WIRING_PI_PIN, LOW);	  // Off
	delay(500);
}