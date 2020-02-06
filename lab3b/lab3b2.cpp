#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string>
#include <math.h>

//Jack Fenton
//Northeastern University
//EECE2150 Embedded Design
//Lab 3b Object Oriented
//30 January 2020


using namespace std;

/*  Initialize Global Variables  */

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

class ZedBoard()
{
private:
	static int fd;
	static char *pBase;

protected:


public:

	ZedBoard();
	~ZedBoard();

	void RegisterWrite(int offset, int value);
	int RegisterRead(int offset);

};

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
	*pBase = (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			*fd, gpio_address);

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
~ZedBoard::ZedBoard()
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





/*  Initialize Functions  */
/*
char *Initialize(int *fd);
void Finalize(char *pBase, int fd);

void Write1Led(char *pBase, int ledNum, int state);
int Read1Led(char *pBase, int ledNum);
void WriteAllLeds(char *pBase, int numLEDs);
int ReadAllLeds(char *pBase);

int Read1Switch(char *pBase, int switchNum);
int ReadAllSwitches(char *pBase);

void ButtonCommands(char *pBase);
int PushButtonGet(char *pBase);
*/

int isInt (string prompt, int min, int max);


int main()
{
	
	int cur_case;
	int numIn, stateIn, stateOut,numOut;


	

	while(cur_case!=6) 

	{
		cout << endl <<
			"Main Menu \n\n" <<
			"1. Change an LED \n" <<
			"2. Read a Switch State \n" <<
			"3. Show a Number on LEDs \n" <<
			"4. Display Number on Switches \n" << 
			"5. Button Pressing Bonanza \n" <<
			"6. Exit \n\n" <<
			"Select and option: ";
		cin >> cur_case;
		if (cin.fail()) 
		{
			cin.clear(); 
			cin.ignore();
		} 
		switch(cur_case)
		{
			case 1:
				//Change LED


				numIn=isInt("Choose an LED to set: ",0,7);
				stateIn=isInt("Choose state for the LED: ",0,1);
				Write1Led(pBase, numIn, stateIn);

				break;

			case 2:
				//Read Switch



				numIn=isInt("Choose a Switch to read: ",0,7);
				stateOut=Read1Switch(pBase, numIn);
				cout<<"The state of Switch "<<numIn<<" is "<<stateOut<<endl;

				break;

			case 3:

				numIn=isInt("Choose number to display on LEDS: ",0,255);
				WriteAllLeds(pBase, numIn);

				break;

			case 4:


				numOut=ReadAllSwitches(pBase);
				cout<<"The 8 bit number made by the switches is "<<numOut<<endl;


				break;
			case 5:
				ButtonCommands(pBase);
				break;

			case 6:
				//exit
				cout << "Exit \n\n";

		}
	}
}

/*  Prints a prompt and takes input, returns input when it is int between min and max */
int isInt(string prompt, int min, int max)
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



class LEDs : public ZedBoard
{
private:
	static int LED_base = 0x12C;


public:
	LEDs(){}
	~LEDs(){}

	void Write1Led(int ledNum, int state);
	void WriteAllLeds(int numLEDs);

	int Read1Led(int ledNum);
	int ReadAllLeds();
};


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



class Switches : public ZedBoard
{
private:
	static int Switch_base = 0x14C;

protected:

public:
	Switches(){}
	~Switches(){}


	int Read1Switch(int switchNum);
	int ReadAllSwitches();
};



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



class Buttons : public ZedBoard
{
private:
	static int Button_base = 0x16C;

protected:

public:
	Buttons(){}
	~Buttons(){}


	int Read1Butt(int buttNum);
	int PushButtonGet();
	void ButtonCommands();
};



int Buttons::Read1Butt(int buttNum)
{
	int buttNum_offset = Button_base + 4*buttNum;
	return RegisterRead(buttNum_offset);
}


void Buttons::ButtonCommands()
{
	int cur_butt=0,last_butt=0,count=0;	

	count=ReadAllSwitches();
	WriteAllLeds(count);
	while(true)
	{	
		//Getting Current Button		
		cur_butt=PushButtonGet();		
		usleep(100000);
		if (cur_butt!=last_butt)
		{
			switch(cur_butt)
			{
				case 1:
					//Shift Digits Right
					count*=2;
					WriteAllLeds(count);
					break;

				case 2:
					//Shift Digits Left
					count/=2;
					WriteAllLeds(count);
					break;

				case 3:
					//Incriment LEDS +1
					count++;
					WriteAllLeds(count);
					ReadAllLeds();
					break;

				case 4:
					//Incriment LEDS -1
					count--;
					WriteAllLeds(count);
					break;

				case 5:

					//Set LEDs to Switches Num
					WriteAllLeds(ReadAllSwitches());
					break;
				case 6:
					//exit
					return;
			}
		}	
		last_butt=cur_butt;

	}
}

int Buttons::PushButtonGet()
{
	int numPress=0;
	for(int i=0; i<5;i++)
	{	
		numPress+=(i+1)*Read1Butt(i);
	}
	return numPress;
}





