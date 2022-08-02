#pragma once
#include <iostream>
#include <exception>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"
#include "fstream"
#include "string"
class DataStructure
{
public:
	DataStructure();//done
	//Constructor that creates empty data structure.
	DataStructure(char* pFilename); //done
	//Constructor that reads data from a binary file.The file was created by function Write(see
	//below).Fails if there occur problems with file handling.
	~DataStructure();//done
	//Destructor that deletes all the items, vectors of pointersand headers.
	DataStructure(const DataStructure &Original); //done
	//Copy constructor.
	int GetItemsNumber();
	//Returns the current number of items in data structure.
	ITEM9* GetItems(char* pID); //done
	//Returns pointer to item with the specified ID.If the item was not found, returns 0.
	void operator+=(ITEM9*);//done
	//Operator function to add a new item into data structure.Fails if the data structure already
	//contains an item with the specified ID.Usage example :
	//DataStructure * pds = new DataStructure;
	//ITEM5* p = (ITEM5*)GetItem(5);
	//*pds += p;
	void operator-=(char* pID);//done
	//Operator function to removeand destroy item with the specified ID.Fails if there is no item with
	//the specified ID.Usage example :
	//*pds -= (char*)”Dark Khaki”;

	DataStructure& operator=(const DataStructure &Right); //done

	//Operator function for assignment.Do not forget that before the assignment you have to destroy
	//all the existing contents.Usage example :
	//DataStructure ds;
	//ds = *pds;
	int operator==(DataStructure &Other); //done
	//Operator function for comparison.Two data structures are equal if they contain the same
	//number of itemsand for each item in the first structure there is a 100 % matching item in the
	//second structure.The order in the linked lists may be different.Returs 0 (not equal) or 1 (equal).
	//Usage example :
	//cout << (ds == *pds) << endl;
	void Write(char* pFilename); //done
	//Serializes the data structureand writes into the specified file.Fails if there occur problems with
	//file handling or if the data structure is empty.
	friend std::ostream& operator<<(std::ostream & ostr, const DataStructure & str);
	//Prints all the items into command prompt window.Usage example :
	//cout << *pds << endl << endl;

	HEADER_A** ppData;

	HEADER_A** InsertItem(HEADER_A** ppData, ITEM9* newItem);

	HEADER_A** RemoveItem(HEADER_A** ppData, char* pItemToRemove);
};

