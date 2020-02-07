// class ZedMenu : private Buttons : private LEDs : private Switches
// {
// private:
// 	int cur_case;
// public:
// 	ZedMenu():Buttons():LEDs():Switches() {cur_case=0}
// 	//~ZedMenu(){}

// 	int Current(){return cur_case;}
// 	void PromptSelection();
// 	void ChooseOption();
// 	void Selection();

// };



// void ZedMenu::PromptSelection()
// {
// 	cout << endl <<
// 			"Main Menu \n\n" <<
// 			"1. Change an LED \n" <<
// 			"2. Read a Switch State \n" <<
// 			"3. Show a Number on LEDs \n" <<
// 			"4. Display Number on Switches \n" << 
// 			"5. Button Pressing Bonanza \n" <<
// 			"6. Exit \n\n";
// }

// void ZedMenu::ChooseOption()
// {
// 		PromptSelection();
// 		cur_case=isInt(1,6, "Select an option: ");
// }

// void ZedMenu::Selection()
// {
// 	switch(cur_case)
// 	{
// 		case 1:
// 			//Change one LED		
// 			Display1Led();
// 			break;

// 		case 2:
// 			//Read Switch
// 			Output1Switch();
// 			break;

// 		case 3:
// 			DisplayAllLeds();
// 			break;

// 		case 4:
// 			OutputAllSwitches();
// 			break;

// 		case 5:
// 			//Push Button Control
// 			ButtonCommands();
// 			break;

// 		case 6:
// 			//exit
// 			cout << "Exit \n\n";
// 			break;
// 	}
// }