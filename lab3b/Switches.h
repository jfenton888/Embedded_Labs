// class Switches : public virtual ZedBoard
// {
// private:
// 	static int Switch_base = 0x14C;

// public:
// 	Switches():ZedBoard(){}
// 	//~Switches(){}


// 	int Read1Switch(int switchNum);
// 	int ReadAllSwitches();

// 	void Output1Switch();
// 	void OutputAllSwitches();
// };



// /* Reads the value of a switch
//  * - Uses base address of I/O
//  * @param switchNum Switch number (0 to 7)
//  * @return Switch value read
//  */
// int Switches::Read1Switch(int switchNum)
// {
// 	int switchNum_offset = Switch_base + 4*switchNum;
// 	return RegisterRead(switchNum_offset);
// }

// int Switches::ReadAllSwitches()
// {
// 	int tempInt=0;
// 	for (int i=0;i<=7;i++)
// 	{
// 		tempInt+=Read1Switch(i)*(int)pow(2,i);
// 	}
// 	return tempInt;
// }

// int Switches::Output1Switch()
// {
// 	int numIn, stateOut;
// 	numIn=isInt(0,7,"Choose a Switch to read: ");
// 	stateOut=Read1Switch(numIn);
// 	cout<<"The state of Switch "<<numIn<<" is "<<stateOut<<endl;
// }

// int Switches::OutputAllSwitches()
// {
// 	cout<<"The 8 bit number made by the switches is "<<ReadAllSwitches()<<endl;
// }
