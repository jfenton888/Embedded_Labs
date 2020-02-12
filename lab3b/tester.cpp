#include <iostream>
#include <stdlib.h> 
#include <ctime>
#include <unistd.h>


using namespace std;


class Buttons
{
private:
	
	int cur_butt;
	int last_butt;
	int count;
	int countRate;
	int countDirection;
	clock_t time_pass;

public:
	Buttons(){cur_butt=0, last_butt=0, count=0; countRate=0; countDirection=1;}
	~Buttons(){}

	void Counter();
	void CounterSpeed();
	void CounterChange();
	

}; //Methods for Buttons on lines 000-000




int main()
{

	clock_t time_pass;
	int countRate=1;

	Buttons testing;
	testing.Counter();

}

void Buttons::Counter()
{
	time_pass = clock();
	count=rand()%100;
	//cout<<count;
	
	while(true)
	{	
		//Getting Current Button		
		
		cin >> cur_butt;
		cout <<cur_butt<<":"<<last_butt<<":"<<countRate<<":"<<count<<endl;

		usleep(100000);
		if (cur_butt!=last_butt)
		{
			CounterSpeed();
		}	
		last_butt=cur_butt;
		CounterChange();
		
	}
}

void Buttons::CounterChange()
{
	if (countRate!=0)
		{

			if((clock()-time_pass)/CLOCKS_PER_SEC>(1/countRate))
			{
				cout<<"increasing";
				count+=countDirection;
				time_pass=clock();
			}
			cout << count <<";"<<(clock()-time_pass)/CLOCKS_PER_SEC<< endl;
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
			count=rand()%100;
			break;

		case 6:
			//exit
			return;
	}
}