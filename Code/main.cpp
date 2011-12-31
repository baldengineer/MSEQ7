#include <WProgram.h>
#include "arduino.h"

/*
	MSGEQ7 - Test Program
	Program to read equalization outputs of a MSGEQ7.

	There are LEDs on pins 3, 5, 6, 9, and 10

	Push button input on pin 2
 */


#define msg7RESET 11
#define msg7Strobe 12
#define msg7DCout 0
const int LEDpins[7] = {3,5,5,6,9,9,10};

#define pushButton 2



void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  for (int x=0; x<7; x++) {
	  pinMode(LEDpins[x], OUTPUT);
  }
  pinMode(msg7RESET, OUTPUT);
  pinMode(msg7Strobe, OUTPUT);

  pinMode(pushButton, INPUT);
  digitalWrite(pushButton, HIGH);  // Enable internal pull-up

  Serial.begin(115200);
}

void loop() {
	digitalWrite(msg7RESET, HIGH);
	delay(5);
	digitalWrite(msg7RESET, LOW);

	for (int x = 0; x < 7; x++)
	{
		digitalWrite(msg7Strobe, LOW);
		delayMicroseconds(35); // to allow the output to settle
		int spectrumRead = analogRead(msg7DCout);

		int PWMvalue = map(spectrumRead, 0, 1024, 0, 255);
		if (PWMvalue < 50)
			PWMvalue = PWMvalue / 2;

		analogWrite(LEDpins[x], PWMvalue);
		digitalWrite(msg7Strobe, HIGH);
	}
	//delay(100);
}



int main(void)
{
	init();

	setup();

	for (;;)
		loop();

	return 0;
}
