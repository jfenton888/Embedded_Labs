#include <iostream>
#include <string>
using namespace std;

struct Person0
{
string name;
int age;
};

void PrintPerson(Person0 *person1);

int main()
{

	Person0 person1;

	person1.name = "John";
	person1.age = 10;

	PrintPerson(&person1);
}

void PrintPerson(Person0 *person1)
{
	cout << person1->name << " is " << person1->age << " years old \n";
}


