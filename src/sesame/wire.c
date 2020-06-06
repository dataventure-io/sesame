/*
	wire.c

	Single-purpose wrapper of the Wiring PI library.  
*/
//#include <stdio.h>
#include <wiringPi.h>

#include "wire.h"

/*
	Send a one-shot signal to pin BCM 17
*/
void wireOneShot()
{
	//fprintf(cgiOut, "wiringPiSetup()<br/>\n");
	wiringPiSetup();

	//fprintf(cgiOut, "pinMode(WIRING_PI_PIN, OUTPUT)<br/>\n");
	pinMode(WIRING_PI_PIN, OUTPUT);

	//fprintf(cgiOut, "digitalWrite(WIRING_PI_PIN, HIGH)<br/>\n");
	digitalWrite(WIRING_PI_PIN, HIGH);  // On

	delay(WIRING_ONE_SHOT_DELAY); // ms

	//fprintf(cgiOut, "digitalWrite(WIRING_PI_PIN, LOW)<br/>\n");
	digitalWrite(WIRING_PI_PIN, LOW);	  // Off

}