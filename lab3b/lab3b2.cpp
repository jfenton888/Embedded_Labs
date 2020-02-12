#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string>
#include <math.h>
#include <ctime>

//Jack Fenton
//Northeastern University
//EECE2150 Embedded Design
//Lab 3b Object Oriented
//6 February 2020


using namespace std;

/* ***** Initialize Global Variables ***** */

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000; 

// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

/*
const int gpio_led1_offset = 0x12C; // Offset for LED1
const int gpio_led2_offset = 0x130; // Offset for LED2
const int gpio_led3_offset = 0x134; // Offset for LED3
const int gpio_led4_offset = 0x138; // Offset for LED4
const int gpio_led5_offset = 0x13C; // Offset for LED5
const int gpio_led6_offset = 0x140; // Offset for LED6
const int gpio_led7_offset = 0x144; // Offset for LED7
const int gpio_led8_offset = 0x148; // Offset for LED8
const int gpio_sw1_offset = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset = 0x150; // Offset for Switch 2
const int gpio_sw3_offset = 0x154; // Offset for Switch 3
const int gpio_sw4_offset = 0x158; // Offset for Switch 4
const int gpio_sw5_offset = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset = 0x160; // Offset for Switch 6
const int gpio_sw7_offset = 0x164; // Offset for Switch 7
const int gpio_sw8_offset = 0x168; // Offset for Switch 8
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button
*/

/* ***** Class Definitions ***** */

class ZedBoard
{
private:
	static int fd;
	static char *pBase;

public:
	ZedBoard();
	~ZedBoard();

	void RegisterWrite(int offset, int value);
	int RegisterRead(int offset);

}; //Methods for ZedBoard on lines 000-000


class LEDs : public virtual ZedBoard
{

private:
	static int LED_base;

public:
	LEDs(){LED_base = 0x12C;}
	~LEDs(){}

	void Write1Led(int ledNum, int state);
	void WriteAllLeds(int numLEDs);

	int Read1Led(int ledNum);
	int ReadAllLeds();

	void Display1Led();
	void DisplayAllLeds();

}; //Methods for LEDs on lines 000-000

class Switches : public virtual ZedBoard
{

private:
	static int Switch_base;

public:
	Switches(){Switch_base = 0x14C;}
	~Switches(){}

	int Read1Switch(int switchNum);
	int ReadAllSwitches();

	void Output1Switch();
	void OutputAllSwitches();

}; //Methods for Switches on lines 000-000


class Buttons : public virtual ZedBoard, public virtual LEDs, public virtual Switches
{
private:
	static int Button_base;
	int cur_butt;
	int last_butt;
	int count;
	int countRate;
	int countDirection;
	clock_t time_pass;

public:
	Buttons(){Button_base = 0x16C, cur_butt=0, last_butt=0, count=0; countRate=0; countDirection=1;}
	~Buttons(){}

	int Read1Butt(int buttNum);
	void PushButtonGet();
	void ButtonCommands();
	void ButtonSelection();
	void Counter();
	void CounterSpeed();
	void CounterChange();
	

}; //Methods for Buttons on lines 000-000


class ZedMenu : private virtual LEDs, private virtual Switches, private Buttons
{
private:
	int cur_case;

public:
	ZedMenu(){cur_case=0;}
	~ZedMenu(){}

	int Current(){return cur_case;}
	void PromptSelection();
	void ChooseOption();
	void Selection();
	

}; //Methods for ZedMenu on lines 000-000


/*  ***** Initialize Non-Class Functions ***** */
int isInt (int min, int max, string prompt);


/* ***** MAIN FUNCTION FOR PROGRAM ***** */
int main()
{
	ZedMenu myZedMenu;
	
	myZedMenu.ChooseOption();
	while(myZedMenu.Current()!=6) 
	{
		myZedMenu.Selection();
		myZedMenu.ChooseOption();
	}
}



/*  Prints a prompt and takes input, returns input when it is int between min and max */
int isInt(int min, int max, string prompt=" ")
{
	int input=-1;
	while((input<min) || (input>max))
	{
		cout << prompt;
		cin >> input;
		if (cin.fail())
		{
			cin.clear(); 
			cin.ignore();
		}
		else break;
	}
	return input;
}




/*
   Initialize general-purpose I/O
 * - Opens access to physical memory /dev/mem
 * - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param fd File descriptor passed by reference, where the result
 * of function 'open' will be stored.
 * @return Address to virtual memory which is mapped to physical,
 * or MAP_FAILED on error.
 */
ZedBoard::ZedBoard()
{
	fd = open( "/dev/mem", O_RDWR);
	*pBase = /*(char*)*/ mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			fd, gpio_address);

	if (pBase == MAP_FAILED)
	{
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1); // Returns 1 to the operating system;
	}
}

/*
 * Close general-purpose I/O.
 *
 * @param pBase Virtual address where I/O was mapped.
 * @param fd File descriptor previously returned by 'open'.
 */
ZedBoard::~ZedBoard()
{
	munmap(pBase, gpio_size);
	close(fd);
}

/*
 * Write a 4-byte value at the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @parem offset Offset where device is mapped.
 * @param value Value to be written.
 */ 
void ZedBoard::RegisterWrite(int offset, int value)
{
	* (int *) (pBase + offset) = value;
} 

/*
 * Read a 4-byte value from the specified general-purpose I/O location.
 * 
 * @param pBase Base address returned by 'mmap'.
 * @param offset Offset where device is mapped.
 * @return Value read.
 */
int ZedBoard::RegisterRead(int offset)
{
	return * (int *) (pBase + offset);
}




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

void LEDs::Display1Led()
{
	int numIn, stateIn;
	numIn=isInt(0,7,"Choose an LED to set: ");
	stateIn=isInt(0,1,"Choose state for the LED: ");
	Write1Led(numIn, stateIn);
}

void LEDs::DisplayAllLeds()
{
	int numIn;
	numIn=isInt(0,255,"Choose number to display on LEDs: ");
	WriteAllLeds(numIn);
}







/* Reads the value of a switch
 * - Uses base address of I/O
 * @param switchNum Switch number (0 to 7)
 * @return Switch value read
 */
int Switches::Read1Switch(int switchNum)
{
	int switchNum_offset = Switch_base + 4*switchNum;
	return RegisterRead(switchNum_offset);
}

int Switches::ReadAllSwitches()
{
	int tempInt=0;
	for (int i=0;i<=7;i++)
	{
		tempInt+=Read1Switch(i)*(int)pow(2,i);
	}
	return tempInt;
}

void Switches::Output1Switch()
{
	int numIn, stateOut;
	numIn=isInt(0,7,"Choose a Switch to read: ");
	stateOut=Read1Switch(numIn);
	cout<<"The state of Switch "<<numIn<<" is "<<stateOut<<endl;
}

void Switches::OutputAllSwitches()
{
	cout<<"The 8 bit number made by the switches is "<<ReadAllSwitches()<<endl;
}






int Buttons::Read1Butt(int buttNum)
{
	int buttNum_offset = Button_base + 4*buttNum;
	return RegisterRead(buttNum_offset);
}


void Buttons::ButtonCommands()
{	

	count=ReadAllSwitches();
	WriteAllLeds(count);
	while(true)
	{	
		//Getting Current Button		
		PushButtonGet();		
		usleep(100000);
		if (cur_butt!=last_butt)
		{
			ButtonSelection();
		}	
		last_butt=cur_butt;
	}
}

void Buttons::PushButtonGet()
{
	int numPress;
	for(int i=0; i<5;i++)
	{	
		numPress+=(i+1)*Read1Butt(i);
	}
	cur_butt=numPress;
}

void Buttons::ButtonSelection()
{
	switch(cur_butt)
	{
		case 1: //Right Button--Shift Digits Right					
			count*=2;
			WriteAllLeds(count);
			break;

		case 2: //Left Button--Shift Digits Left					
			count/=2;
			WriteAllLeds(count);
			break;

		case 3: //Up Button--Incriment LEDS +1		
			count++;
			WriteAllLeds(count);
			ReadAllLeds();
			break;

		case 4: //Down Button--Incriment LEDS -1
			count--;
			WriteAllLeds(count);
			break;

		case 5: //Center Button--Set LEDs to Switches Num	
			WriteAllLeds(ReadAllSwitches());
			break;

		case 6:
			//exit
			return;
	}
}


void Buttons::Counter()
{
	time_pass = clock();
	count=ReadAllSwitches();
	WriteAllLeds(count);
	
	while(true)
	{	
		//Getting Current Button		
		PushButtonGet();		
		usleep(100000);
		if (cur_butt!=last_butt)
		{
			CounterSpeed();
			CounterChange();
		}	
		last_butt=cur_butt;
		
	}
}

void Buttons::CounterChange()
{
	if (countRate!=0)
		{
			if((clock()-time_pass)/CLOCKS_PER_SEC>1/countRate)
			{ 
				count+=countDirection;
				time_pass=clock();
			}
			WriteAllLeds(count);
		}

}


void Buttons::CounterSpeed()
{
	switch(cur_butt)
	{
		case 1: //Right Button--Counts Up					
			countDirection=1;
			break;

		case 2: //Left Button--Count Down					
			countDirection=-1;
			break;

		case 3: //Up Button--Increase Count Speed	
			countRate++;
			break;

		case 4: //Down Button--Incriment LEDS -1
			if (countRate>0) countRate--;
			break;

		case 5: //Center Button--Set LEDs to Switches Num	
			count=ReadAllSwitches();
			break;

		case 6:
			//exit
			return;
	}
}


void ZedMenu::PromptSelection()
{
	cout << endl <<
			"Main Menu \n\n" <<
			"1. Change an LED \n" <<
			"2. Read a Switch State \n" <<
			"3. Show a Number on LEDs \n" <<
			"4. Display Number on Switches \n" << 
			"5. Button Pressing Bonanza \n" <<
			"6. Counter Speed Control \n" <<
			"7. Exit \n\n";
}

void ZedMenu::ChooseOption()
{
		PromptSelection();
		cur_case=isInt(1,7, "Select an option: ");
}

void ZedMenu::Selection()
{
	switch(cur_case)
	{
		case 1:
			//Change one LED		
			Display1Led();
			break;

		case 2:
			//Read Switch
			Output1Switch();
			break;

		case 3:
			DisplayAllLeds();
			break;

		case 4:
			OutputAllSwitches();
			break;

		case 5:
			//Push Button Control
			ButtonCommands();
			break;
		case 7:
			CounterSpeed();
		case 6:
			//exit
			cout << "Exit \n\n";
			break;
	}
}


