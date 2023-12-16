#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include "string.h"


typedef struct PDirectory {
	char* phoneNumber;
	char* name;
	struct PDirectory* newNode;
}PDirectory;

PDirectory* first = NULL;									//Used to point to the first node in the linked list
void displayPDirectory();
PDirectory* createRecord();
int push(PDirectory* newrec);
int searchAndDestroy(char* phoneNum);
PDirectory* search(char* phoneNum, int* flag);
PDirectory* search2(char* query, int option);
void displayMenu();

int main()
{
	int choice;					 //choice for switch
	char query[20];				 //string for switch
	PDirectory* searchrec;		

	displayMenu();
	
	while(1)
	{
	puts("Enter your choice?");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		puts("Displaying phone directory");
		displayPDirectory();
		break;

	case 2:
		push(createRecord());
		break;

	case 3:
		puts("Enter phonenumber: ");
		scanf("%s", query); 
		searchAndDestroy(query);
		break;

	case 4:
		puts("Enter phonenumber: ");
		scanf("%s", query);
		searchrec = search2(query, 1);
		if (searchrec == NULL)						//if the searchrecord does not exist print the string
		{
			puts("phonenumber not found");
		}
		else										//else print the string
		{
		printf("the person with phonenumber: %s\n is called: %s\n", query, searchrec->name); 
		}
		break;

	case 5:
		puts("Enter name: ");
		scanf("%s", query);
		searchrec = search2(query, 0);
		if (searchrec == NULL)      //if the search record does not exist print the string
		{
			puts("No name found");
		}
		else
		{
		printf("%s has the phonenumber: %s\n", query, searchrec->phoneNumber);	//else print this string
		}
		break;

	default:
		puts("Enter valid option"); //if invalid option print menu again
		displayMenu();
		break;
	}
	}
}

//1
void displayPDirectory()
{
	int ordNum = 1;											//The ordinal number starts on one 
	PDirectory* temp = first;								//temporary pointer
	while (temp != NULL)									//while there is a node the loop will continue
	{
		printf("\n%d:\n", ordNum);							//prints the Ordinal Number in the phone directory
		temp->name;											//points to the name of the current node
		printf("Name: %s\n", temp->name);					//prints the name of the first
		temp->phoneNumber;									//points to the phonenumber of the current node
		printf("PhoneNumber: %s\n", temp->phoneNumber);		//prints the phonenumber of the current node
		temp = temp->newNode;								//goes on to the next node in the Linked list
		ordNum++;											//Adds 1 to the Ordinal number before moving on to the next
	}
}

//2
PDirectory* createRecord()
{
	struct PDirectory* new_node = (struct PDirectory*)malloc(sizeof(PDirectory)); //the new node 
	if (new_node == NULL) exit(0);												  //if there is not any available memory exit
	char* name = (char*)malloc(sizeof(char[30]));								  //allocate memory for name
	puts("Enter name: ");														  
	scanf("%s", name);
	char* phoneNumber = (char*)malloc(sizeof(char[30]));						  //allcoate memory for phonenumber
	puts("Enter phonenumber: ");
	scanf("%s", phoneNumber);
	new_node->phoneNumber = phoneNumber;										  //passes the input values to the new node
	new_node->name = name;														  
	return new_node;															  //returns the new node
}

//3
int push(PDirectory* newrec)
{
	PDirectory* temp = first;						//temporary pointer to the push function
	while (temp != NULL) {							
		temp = temp->newNode;						//loops the ptr through the list to see if the values already exsits
		if (newrec == temp) return -1;				//if the node already exists return -1
	}
	newrec->newNode = first;						//if the node does not exist makes it the first and returns 0
	first = newrec;
	return 0;
}

//4
int searchAndDestroy(char* phoneNum)
{
	int found;			

	PDirectory* pretemp = search(phoneNum, &found);		//a temp ptr that is one node before the temp pointer
	if (found == 0)										//if the value of found is 0 then the programme could not find the record
	{
		return -1;
	}
	if (pretemp == NULL)								//if the found value is the first the pretemp is null
	{												
		PDirectory* temp = first;						//the pointer then needs to be moved before removing the node
		first = first->newNode;						
		free(temp);
	}
	else
	{
		PDirectory* temp = pretemp->newNode;			//if the value is not in the beginning of the list
		pretemp->newNode = pretemp->newNode->newNode;	
		free(temp);
	}
	return 0;
}

//5
PDirectory* search(char* phoneNum, int* flag)
{
	PDirectory* temp = first;						  //temp ptr
	PDirectory* pretemp = NULL;						 

	while (temp != NULL)							  //loops through the linked list until the end
	{
		if (strcmp(temp->phoneNumber, phoneNum) == 0) //compares the string of the phonenumber and the phonenum you search for
		{
			*flag = 1;								  //the flag is equal to one if the value is found
			return pretemp;								
		}
		pretemp = temp;								  
		temp = temp->newNode;						  //after the first value is checked the move to next node
	}

	*flag = 0;										  //if the value is not found the flag is equal to 0
	return pretemp;
}

//6
PDirectory* search2(char* query, int option)
{
	PDirectory* temp = first;							//tempptr
	while (temp != NULL)								//loops through the linked list
	{
		if (option == 1) {								//if option	1 search the phone number 
			if (strcmp(temp->phoneNumber, query) == 0)	//if the phonenumber is equal to the query return the node
				return temp;
		}
		if (option == 0) {								//option 0 and you will check after name 
			if (strcmp(temp->name, query) == 0)			//compares the input with the name
				return temp;							//returns the node
		}
		temp = temp->newNode;							//moves the ptr to the next node after the value of the first has been checked
	}
	return NULL;
}

void displayMenu()
{
	puts("MAIN MENU OF THE PHONE DIRECTORY");
	puts("Enter 1 to display phone directory");
	puts("Enter 2 to enter a record data to the phone directory");
	puts("Enter 3 to delete a phone number");
	puts("Enter 4 to search for a phone number in the phone directory");
	puts("Enter 5 to search for a phone number or name in the phone directory");
}


