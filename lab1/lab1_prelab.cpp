#include <iostream>
#include <stdlib.h>

//Jack Fenton
//Northeastern University
//EECE2150 Embedded Design
//Lab 1 Pre-Lab


using namespace std;

/*  Initialize Global Variables  */

int count;
int size;
double *v ;

/*  Initialize Functions  */
void Initialize();
void Finalize();



int main()
{
	int cur_case;
	Initialize();

	trySwitch:
		switch(cur_case)
		{
			case 1:
			//printing
				cout << "Case 1 \n";
				goto Prompt;		

			case 2:
			//append
				cout << "Case 2 \n";
				goto Prompt;

			case 3:
			//remove
				cout << "Case 3 \n";
				goto Prompt;

			case 4:
			//insert
				cout << "Case 4 \n";
				goto Prompt;

			case 5:
				cout << "Case 5 \n";
				break;

			default:
				Prompt:
					//will only allow integer inputs through
					while (true) 
					{
						cout << "Main Menu \n\n" <<
								"1. Pring the Array \n" <<
								"2. Append element at the end \n" <<
								"3. Remove last element \n" <<
								"4. Insert one element \n" <<
								"5. Exit \n\n" <<
								"Select and option: ";
        				cin >> cur_case;
				        if (cin.fail()) 
				        {
				            cin.clear(); cin.ignore();
				        } 
				        else break;
					}
					goto trySwitch;

		}


	Finalize();
}


/*  Set initial values for global variables  */
void Initialize()
{
	int count=0;
	int size=2;
	double *v=new double[size];

}

/*  Clears memory space allocated to vector  */
void Finalize()
{
	delete[] v;

}

