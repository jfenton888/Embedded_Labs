#include <iostream>
#include <stdlib.h>
#include <string>

//Jack Fenton
//Northeastern University
//EECE2150 Embedded Design
//Lab 1


using namespace std;

/*  Initialize Global Variables  */

int counter;
int size;
double *v;

/*  Initialize Functions  */
void Initialize();
void Finalize();
void Grow();
void DropEnd();
void AddElement();
void AddElement(int elIndex);
void PrintVector();
void RemoveElement();
void InsertElement();
void Shift(int elIndex);
int isInt (string prompt);

int main()
{
	int cur_case;
	Initialize();

	while(cur_case!=5) 
	{
		cout << endl <<
				"Main Menu – Size:" <<size<< " Count: "<<counter<< "\n\n" <<
				"1. Print the Array \n" <<
				"2. Append element at the end \n" <<
				"3. Remove last element \n" <<
				"4. Insert one element \n" <<
				"5. Exit \n\n" <<
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
			//printing
				cout << "Printing the Array \n\n";
				PrintVector();
				break;

			case 2:
			//append
				cout << "Append element at the end \n\n";
				AddElement();
				break;

			case 3:
			//remove
				cout << "Remove last element \n\n";
				RemoveElement();
				break;

			case 4:
			//insert
				cout << "Insert one element \n\n";
				InsertElement();
				break;

			case 5:
			//exit
				cout << "Exit \n\n";

		}
	}

	Finalize();
}



/*  Set initial values for global variables  */
void Initialize()
{
	counter=0;
	size=2;
	v=new double[size];
	cout<<"Initialized \n";
}

/*  Clears memory space allocated to vector  */
void Finalize()
{
	delete[] v;
	cout<<"Completed \n";
}

/*  Prints a prompt and takes input, returns input when it is int */
int isInt(string prompt)
{
	int input;
	while(true)
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


/*  Prints all elements with values in vector  */
void PrintVector()
{
for(int i=0;i<counter;i++) cout<<v[i]<<endl;
}


/*  
Creates new larger vector with all data from v
Frees memory of smaller vector
Points v to new memory space
*/
void Grow()
{
	//cout <<"Previous capacity: "<<size<<" element \n";
	double *nv=new double[++size];
	for(int i=0;i<size-1;i++) nv[i]=v[i];
	delete[] v;
	v=nv;
	//cout <<"New capacity: "<<size<<" element \n";
}

/*  Same as Grow() but decreases vector to half its original size  */
void Shrink()
{
	size/=2;
	double *nv=new double[size];
	for(int i=0;i<size-1;i++) nv[i]=v[i];
	delete[] v;
	v=nv;
}


/* 
Same as Grow() but makes array of same size and does not add last element
*/
void DropEnd()
{
	--counter;
	double *nv=new double[size];
	for(int i=0;i<counter;i++) nv[i]=v[i];
	delete[] v;
	v=nv;
	
}

/* 
Adds element at next unused position in array
*/
void AddElement()
{
	if (counter==size) Grow();
	v[counter]=isInt("Enter the new element: ");
	counter++;
}


/* 
Adds element at specified position in the array
*/
void AddElement(int elIndex)
{
	if (counter==size) Grow();
	v[elIndex]=isInt("Enter the new element: ");
	counter++;
}





/*  Removes value from the last position in array with value  */
void RemoveElement()
{
	if (counter==0) cout << "This array is already empty \n";
	else  DropEnd();
	//while (.3*size>counter) Shrink();

}

/* 
user gives input of poition to add element 
space is made at that position
element is added at that poisition
*/
void InsertElement()
{
	int elIndex;
	do{
	elIndex=isInt("Enter index of the new element: ");
	}while (elIndex>counter);

	Shift(elIndex);
	AddElement(elIndex);

}

/*  Shifts all elements at or after user index to make room for new element */
void Shift(int elIndex)
{
	if (counter==size) Grow();
	for(int i=counter; i>=elIndex; i--) v[i]=v[i-1];
}






