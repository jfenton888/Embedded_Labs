#include <iostream>
#include <stdlib.h>

#include "Array.h"

using namespace std;


void Array::PrintArray( int v[], int size)
{
	for(int i=0;i<size;i++) cout<< v[i] << " ";
	cout << endl;
}

void Array::RandomArray(int v[], int size)
{

	for (int i=0; i<size;i++)
	{
		v[i]=rand()%100;
	}

}

void Array::SortArray(int v[], int size)
{
	int i, j, min_idx, temp;
	for (i=0;i<size-1;i++)
	{
		min_idx=i;
		for (j=i+1;j<size;j++)
		{
			if (v[j]<v[min_idx])
				{
					min_idx=j;

				}
		}
		//swapping
		temp=v[min_idx];
		v[min_idx]=v[i];
		v[i]=temp;

	}

}

