
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "WiimoteAccel.h"
#include "ZedBoard.h"

using namespace std;

class WiimoteToLed : public WiimoteAccel
{
private:
	ZedBoard *zed_board; 

public:
	WiimoteToLed(ZedBoard *zb){zed_board=zb;}
	void AccelerationEvent(int code, int acceleration)
	{
		if(code==3)
		{
						
		}		
	}
}






int main()
{
	// Instantiate ZedBoard object statically
	ZedBoard zed_board;

	// Instantiate WiimoteToLed object statically, passing a pointer to the
	// recently created ZedBoard object.
	WiimoteToLed wiimote_to_led(&zed_board);

	// Enter infinite loop listening to events. The overridden function
	// WiimoteToLed::AccelerationEvent() will be invoked when the user moves
	// the Wiimote.
	wiimote_to_led.Listen();

	// Unreachable code, previous function has an infinite loop
	return 0;
}


