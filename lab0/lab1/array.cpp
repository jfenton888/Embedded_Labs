#include <iostream>
#include <stdlib.h>

using namespace std;

//Prints array in a single line
void PrintArray( int v[], int size)
{
	for(int i=0;i<size;i++) cout<< v[i] << " ";
	cout << endl;
}

//Initializes a random number 0-99 to each position in the array
void RandomArray(int v[], int size)
{
	for (int i=0; i<size;i++)
	{
		v[i]=rand()%100;
	}
}

//Sorts the values in the array
void SortArray(int v[], int size)
{
	int i, j, min_idx, temp;
	//starting from the left, keeps swapping so no values behind it are smaller
	for (i=0;i<size-1;i++)
	{
		min_idx=i;
		//compares all following values with the minimum index
		for (j=i+1;j<size;j++)
		{
				//makes new min index if smaller than i
				if (v[j]<v[min_idx])
				{
					min_idx=j;
				}
		}
		//swaps with new min index
		temp=v[min_idx];
		v[min_idx]=v[i];
		v[i]=temp;
	}
}

int main ()
{
	int size=10;
	int v[10];
	//unsorted array
	RandomArray(v,size);
	PrintArray(v,size);
	//sorting array
	SortArray(v,size);
	PrintArray(v,size);

}


