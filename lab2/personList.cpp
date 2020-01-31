#include <iostream>
#include <string>
using namespace std;

//Jack Fenton and Michael Delaney
//Northeastern University
//EECE2150 Embedded Design
//Lab 2
//30 January 2020

// Linked List Management Code
struct Person
{
	// Unique identifier for the person
	int id;
	// Information about person
	string name;
	int age;
	// Pointer to next person in list
	Person *next;
};
struct List
{
	// First person in the list. A value equal to NULL indicates that the
	// list is empty.
	Person *head;
	// Current person in the list. A value equal to NULL indicates a
	// past-the-end position.
	Person *current;
	// Pointer to the element appearing before 'current'. It can be NULL if
	// 'current' is NULL, or if 'current' is the first element in the list.
	Person *previous;
	// Number of persons in the list
	int count;
};

//Initialize Functions
void ListInitialize(List *list);
void ListNext(List *list);
void ListHead(List *list);
Person *ListGet(List *list);
void ListFind(List *list, int id);
void ListInsert(List *list, Person *person);
void ListRemove(List *list);
void PrintPerson(Person *person);

//User Functions
void AddPerson(List *list);
void FindPerson(List *list);
void RemovePerson(List *list);
void PrintList(List *list);
int inInt(string prompt);
string inString(string prompt);



/* main function: Will create and process a linked list */
int main() {
	List list;				// Create the main list
	ListInitialize(&list);	// Initialize the list
	int cur_case;
	while(cur_case!=5) 
	{
		cout << endl <<
				"Main Menu \n\n" <<
				"1. Add a person \n" <<
				"2. Find a person \n" <<
				"3. Remove a person \n" <<
				"4. Print the list \n" <<
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
			//adding person
				cout << "Add a person \n\n";
				AddPerson(&list);	
				break;

			case 2:
			//find person
				cout << "Find a person \n\n";
				FindPerson(&list);
				break;

			case 3:
			//remove person
				cout << "Remove a person \n\n";
				RemovePerson(&list);
				break;

			case 4:
			//print list
				cout << "Print the list \n\n";
				PrintList(&list);
				break;

			case 5:
			//exit
				cout << "Exit \n\n";
		}
	}
	return 0;
} 
//end main


// Give an initial value to all the fields in the list.
void ListInitialize(List *list)
{
	list->head = NULL;
	list->current = NULL;
	list->previous = NULL;
	list->count = 0;
}

// Move the current position in the list one element forward. If last element
// is exceeded, the current position is set to a special past-the-end value.
void ListNext(List *list)
{
	if (list->current)
	{
		list->previous = list->current;
		list->current = list->current->next;
	}
}

// Move the current position to the first element in the list.
void ListHead(List *list)
{
	list->previous = NULL;
	list->current = list->head;
}

// Get the element at the current position, or NULL if the current position is
// past-the-end.
Person *ListGet(List *list)
{
	return list->current;
}

// Set the current position to the person with the given id. If no person
// exists with that id, the current position is set to past-the-end.
void ListFind(List *list, int id)
{
	ListHead(list);
	while (list->current && list->current->id != id)
		ListNext(list);
}

// Insert a person before the element at the current position in the list. If
// the current position is past-the-end, the person is inserted at the end of
// the list. The new person is made the new current element in the list.
void ListInsert(List *list, Person *person)
{
	// Set 'next' pointer of current element
	person->next = list->current;
	// Set 'next' pointer of previous element. Treat the special case where
	// the current element was the head of the list.
	if (list->current == list->head)
		list->head = person;
	else
		list->previous->next = person;
	// Set the current element to the new person
	list->current = person;
}

// Remove the current element in the list. The new current element will be the
// element that appeared right after the removed element.
void ListRemove(List *list)
{
	// Ignore if current element is past-the-end
	if (!list->current)
		return;
	// Remove element. Consider special case where the current element is
	// in the head of the list.
	if (list->current == list->head)
		list->head = list->current->next;
	else
		list->previous->next = list->current->next;
	// Free element, but save pointer to next element first.
	Person *next = list->current->next;
	delete list->current;
	// Set new current element
	list->current = next;
}

void PrintPerson(Person *person)
{
	cout << "Person with ID: " << person->id << endl;
	cout << "\t  Name: " << person->name << endl;
	cout << "\t   Age: " << person->age << endl << endl;;
}

/*  Prints a prompt and takes input, returns input when it is int */
int inInt(string prompt)
{
	int inputInt;
	while(true)
	{
		cout << prompt;
		cin >> inputInt;
		if (cin.fail())
		{
			cin.clear(); 
			cin.ignore();
		}
		else break;
	}
	return inputInt;
}

/*  Prints a prompt and takes input, returns input as a string */
string inString(string prompt)
{
	string inputStr;
	cout << prompt;	
	cin >> inputStr;
	return inputStr;
}


/* 
Creates new newGuy, an empty struct with atributes of person
Assigns id, assigns name and age based on user input
From wherever the current position was, moves forward until position is one after last defined person
Assigns last previously defined person to point to newGuy
*/
void AddPerson(List *list)
{
	Person *newGuy;
	newGuy= new Person;
	
	newGuy->id=list->count+1;
	newGuy->name=inString("Person's Name: ");
	newGuy->age=inInt("Person's Age: ");
	cout << endl;

	while (list->current!=NULL) ListNext(list);
	ListInsert(list, newGuy);	
	list->count++;


}
/* New printing function that prints all data for one person on single line */
void PrintList(List *list)
{
	ListHead(list);
	while(list->current!=NULL)
	{
	cout << "id: "<< list->current->id << " Name: " << list->current->name << "  Age: " <<list->current->age << endl; 
	ListNext(list);
	}
}

/* 
User declares id of person they want information for 
ListFind() iterates through until current id is the one requested
PrintPerson() outputs information about person
*/
void FindPerson(List *list)
{
	int findID;
	do
	{
	findID=inInt("id for information: ");
	if (findID<=list->count) break;
	else cout << "This is not a valid id \n";
	} while(true);

	ListFind(list, findID);
	PrintPerson(list->current);

}
/* 
Same way as FindPerson(), sets current position to the user input
Use predefined function to remove specified person  
Reassigns previous element to point to one that follows
*/
void RemovePerson(List *list)
{
	int findID;
	do
	{
	findID=inInt("id to remove: ");
	if (findID<=list->count) break;
	else cout << "This is not a valid id \n";
	} while(true);

	ListFind(list, findID);
	ListRemove(list);

}


