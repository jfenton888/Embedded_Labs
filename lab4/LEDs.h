
#ifndef _LEDS_
#define _LEDS_

#include "ZedBoard.h"


class LEDs : public virtual ZedBoard
{

private:
	int LED_base;

public:
	LEDs(){LED_base = 0x12C;}
	~LEDs(){}

	void Write1Led(int ledNum, int state);
	void WriteAllLeds(int numLEDs);

	int Read1Led(int ledNum);
	int ReadAllLeds();

}; //Methods for LEDs on lines 000-000

#endif
