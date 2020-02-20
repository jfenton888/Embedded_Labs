#include "LEDs.h"


/* Changes the state of an LED (ON or OFF)
 * @param ledNum LED number (0 to 7)
 * @param state State to change to (ON or OFF)
 */
void LEDs::Write1Led(int ledNum, int state)
{
	int ledNum_offset = LED_base + 4*ledNum;
	RegisterWrite(ledNum_offset, state);
}

void LEDs::WriteAllLeds(int numLEDs)
{
	for (int i=0;i<=7;i++) 
	{
		Write1Led(i, numLEDs%2);
		numLEDs/=2;
	}
}

/* Reads the value of an LED
 * - Uses base address of I/O
 * @param ledNum LED number (0 to 7)
 * @return LED value read
 */
int LEDs::Read1Led(int ledNum)
{
	int ledNum_offset = LED_base + 4*ledNum;
	return RegisterRead(ledNum_offset);
}

int LEDs::ReadAllLeds()
{
	int tempInt=0;
	for (int i=0;i<=7;i++)
	{
		tempInt+=Read1Led(i)*(int)pow(2,i);
	}
	return tempInt; 
}

