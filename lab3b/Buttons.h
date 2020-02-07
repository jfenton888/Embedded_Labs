// class Buttons : public virtual ZedBoard
// {
// private:
// 	static int Button_base = 0x16C;
// 	int cur_butt=0;
// 	int last_butt=0;
// 	int count=0;

// public:
// 	Buttons():ZedBoard(){}
// 	~Buttons(){}

// 	int Read1Butt(int buttNum);
// 	int PushButtonGet();
// 	void ButtonCommands();
// 	void ButtonSelection();
// };



// int Buttons::Read1Butt(int buttNum)
// {
// 	int buttNum_offset = Button_base + 4*buttNum;
// 	return RegisterRead(buttNum_offset);
// }


// void Buttons::ButtonCommands()
// {	

// 	count=ReadAllSwitches();
// 	WriteAllLeds(count);
// 	while(true)
// 	{	
// 		//Getting Current Button		
// 		cur_butt=PushButtonGet();		
// 		usleep(100000);
// 		if (cur_butt!=last_butt)
// 		{
// 			ButtonSelection();
// 		}	
// 		last_butt=cur_butt;
// 	}
// }

// void Buttons::PushButtonGet()
// {
// 	int numPress;
// 	for(int i=0; i<5;i++)
// 	{	
// 		numPress+=(i+1)*Read1Butt(i);
// 	}
// 	cur_butt=numPress;
// }

// void Buttons::ButtonSelection()
// {
// 	switch(cur_butt)
// 	{
// 		case 1: //Shift Digits Right					
// 			count*=2;
// 			WriteAllLeds(count);
// 			break;

// 		case 2: //Shift Digits Left					
// 			count/=2;
// 			WriteAllLeds(count);
// 			break;

// 		case 3: //Incriment LEDS +1		
// 			count++;
// 			WriteAllLeds(count);
// 			ReadAllLeds();
// 			break;

// 		case 4: //Incriment LEDS -1
// 			count--;
// 			WriteAllLeds(count);
// 			break;

// 		case 5: //Set LEDs to Switches Num	
// 			WriteAllLeds(ReadAllSwitches());
// 			break;

// 		case 6:
// 			//exit
// 			return;
// 	}
// }
