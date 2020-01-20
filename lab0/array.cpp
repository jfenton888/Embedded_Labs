#include <iostream>
#include <stdlib.h>

using namespace std;

void PrintArray( int v[], int size)
{
	for(int i=0;i<size;i++) cout<< v[i] << " ";
	cout << endl;
}

void RandomArray(int v[], int size)
{

	for (int i=0; i<size;i++)
	{
		v[i]=rand()%100;
	}

}

void SortArray(int v[], int size)
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

int main ()
{
	int size=10;
	int v[10];
	RandomArray(v,size);
	PrintArray(v,size);
	SortArray(v,size);
	PrintArray(v,size);

}
