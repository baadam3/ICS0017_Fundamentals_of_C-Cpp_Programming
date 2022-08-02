/*#include <iostream>
#include <exception>
#include "DateTime.h"
#include "Items.h"
#include "Headers.h"
#include "ICS0017DataSource.h"*/
#include "DataStructure.h"


void PrintDataStructure(HEADER_A** ppData)
{
	HEADER_A** ppClone = &(*ppData); //clone so the original data won't get modified

	int cc2 = 0;
	int isEmpty = 0;
	while (cc2 < 26)
	{
		if (ppClone[cc2] == NULL)
		{
			isEmpty++;
		}
		cc2++;
	}
	try
	{
		if (isEmpty == 26) //if no data structure was inicialized throw an error and return
		{
			throw "Empty data structure!";
		}
	}
	catch (const char *e)
	{
		std::cout << e << std::endl;
		return;
	}
	
	int cc = 0;
	int itemCounter = 1;
	while (cc < 26) //it is fixed that we have 26 pointers
	{
		if (ppClone[cc] != NULL)
		{
			HEADER_A* pLinkedList = ppClone[cc]; //pointer to move so original data won't get corrupted

			while (pLinkedList != NULL)//going through the list of Headers of sub items
			{
				ITEM9* pSubItem = (ITEM9*)pLinkedList->pItems;
				while (pSubItem != NULL) // going through the linked list of sub items
				{
					DATE3* pDate = (DATE3*)pSubItem->pDate;
					std::cout << itemCounter++ << ") " << pSubItem->pID << " " << pSubItem->Code << " " << pDate->Day << " " << pDate->pMonth << " " << pDate->Year << std::endl;
					pSubItem = pSubItem->pNext;
				}
				
				pLinkedList = pLinkedList->pNext;

			}
		}
		cc++;
	}
}

HEADER_A** InsertItem(HEADER_A** ppData, char* pNewItem = 0)
{
	HEADER_A** ppClone = &(*ppData); //clone so the original data won't get modified

	int cc2 = 0;
	int isEmpty = 0;
	while (cc2 < 26)
	{
		if (ppClone[cc2] == NULL)
		{
			isEmpty++;
		}
		cc2++;
	}
	try
	{
		if (isEmpty == 26) //if no data structure was inicialized throw an error and return
		{
			throw "Empty data structure!";
		}
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
		return ppData;
	}
	//checking if given item is formatted correctly
	int whiteSpaces = 0;
	for (int i = 0; i < strlen(pNewItem); i++)
	{
		int isSpcae = isspace(pNewItem[i]);
		if (isSpcae != 0)
		{
			whiteSpaces++;
			try
			{
				if (whiteSpaces > 1)
				{
					throw "Presented ID does not follow formatting rules!";
				}
			}
			catch (const char *e)
			{
				std::cout << "An error occured: " << e << std::endl;
				return ppData;
			}
		}
	}
	if (whiteSpaces == 0)
	{
		try
		{
			throw "Presented ID does not follow formatting rules!";
		}
		catch (const char* e)
		{
			std::cout << "An error occured: " << e << std::endl;
			return ppData;
		}
	}

	int cc = 0;
	ITEM9* itemToInsert = (ITEM9*)GetItem(9, pNewItem);
	while (cc < 26) //it is fixed that we have 26 pointers
	{	

		HEADER_A* pLinkedList = ppClone[cc]; //pointer to move so original data won't get corrupted
		if (ppClone[cc] != NULL)
		{
			while (pLinkedList != NULL)//going through the list of sub items
			{
				ITEM9* pSubItem = (ITEM9*)pLinkedList->pItems;
				while (pSubItem != NULL)
				{
					try
					{
						if (strcmp(pSubItem->pID, itemToInsert->pID) == 0)
						{
							throw "This data already exists!";
						}
					}
					catch (const char* e)
					{
						std::cout << e << std::endl;
						return ppData;
					}
					pSubItem = pSubItem->pNext;
				}
				
				
				pLinkedList = pLinkedList->pNext;
			}
		}
		cc++;
	}
  //we did not find the item in the list
	cc = 0;
	int cBeginIndex = 0;
	for (int i = 0; i < strlen(itemToInsert->pID); i++) //calculating beginning of second word
	{
		if ((int)(itemToInsert->pID[i]) == 32)
		{
			cBeginIndex = i + 1;
		}
	}
	while (cc < 26) //it is fixed that we have 26 pointers
	{
		HEADER_A* pLinkedList = ppClone[cc]; //pointer to move so original data won't get corrupted
		bool isFirstIteration = true;
		

		if (ppClone[cc] != NULL)
		{
			

			if (int(((ITEM9*)(ppClone[cc]->pItems))->pID[0]) < int(itemToInsert->pID[0])) //if ascii value of currect words 1st letter is smaller then positin cc to where it should be
			{
				cc += int(itemToInsert->pID[0]) - int(((ITEM9*)(ppClone[cc]->pItems))->pID[0]);

			}
			else if (int(((ITEM9*)(ppClone[cc]->pItems))->pID[0]) > int(itemToInsert->pID[0])) //if ascii value of currect words 1st letter is greater then positin cc to where it should be
			{
				cc += int(itemToInsert->pID[0]) - int(((ITEM9*)(ppClone[cc]->pItems))->pID[0]);
			}
			

			if (ppClone[cc] == NULL) // if Main hader doesn't exist it will create it and insert the new item to the list
			{
				ppClone[cc] = new HEADER_A;
				if (ppClone[cc - 1] != NULL && cc != 0)
				{
					ppClone[cc]->pNext = ppClone[cc - 1]->pNext;
				}
				else
				{
					ppClone[cc]->pNext = NULL;
				}

				ppClone[cc]->pItems = itemToInsert;
				ppClone[cc]->cBegin = itemToInsert->pID[cBeginIndex];
				return ppData;
			}
			pLinkedList = ppClone[cc];
			ITEM9* pSubItem = (ITEM9*)pLinkedList->pItems;
			

			if (pSubItem->pID[0] == itemToInsert->pID[0]) //checking if 1st letters match
			{
				
				while (pLinkedList != NULL)//going through the list of sub items
				{
					if (pLinkedList->cBegin != NULL && pLinkedList->cBegin == itemToInsert->pID[cBeginIndex] && pSubItem != NULL)//If 1st letter and cBegin exists it inserts
					{
						itemToInsert->pNext = pSubItem->pNext;

						pSubItem->pNext = itemToInsert;

						HEADER_A* newNode = new HEADER_A;
						
						newNode->pItems = itemToInsert;
						
						newNode->cBegin = itemToInsert->pID[cBeginIndex];
						if (pLinkedList->pNext == NULL)
						{
							newNode->pNext = NULL;
						}
						else
						{
							newNode->pNext = pLinkedList->pNext;
						}

						return ppData;
					}

					/*if (pSubItem != NULL)
					{
						pSubItem = pSubItem->pNext;
					}*/
					/*else*/ if (pLinkedList != NULL)
					{
						pSubItem = (ITEM9*)pLinkedList->pItems;
					}
					if (!isFirstIteration)
					{
						pLinkedList = pLinkedList->pNext;
					}
					else
					{
						isFirstIteration = false;
					}

				}
				// cBegin did not exist in the list

				isFirstIteration = true;
				pLinkedList = ppClone[cc];
				HEADER_A* pLinkedListFront = pLinkedList;
				HEADER_A* node = new HEADER_A;
				
				while (pLinkedList != NULL)//going through the list of sub items
				{
					pSubItem = (ITEM9*)pLinkedList->pItems;

					while (pSubItem != NULL)
					{
						if (int(itemToInsert->pID[cBeginIndex]) < int(pLinkedList->cBegin)) // if itemToInsert's cBegin smaller then 1st letter's cBegin insert it before
						{
							ppClone[cc] = node;
							node->pNext = pLinkedList;
							node->pItems = itemToInsert;
							node->cBegin = itemToInsert->pID[cBeginIndex];
							return ppData;
						}
						while (int(itemToInsert->pID[cBeginIndex]) > int(pLinkedListFront->cBegin)) // if itemToInsert cBegin is between 2 values insert between
						{
							pLinkedList = pLinkedList->pNext;
							if (pLinkedList == NULL)
							{
								node->pItems = itemToInsert;
								node->cBegin = itemToInsert->pID[cBeginIndex];
								node->pNext = NULL;
								pLinkedListFront->pNext = node;
								return ppData;
							}
							if (int(itemToInsert->pID[cBeginIndex]) < int(pLinkedList->cBegin))
							{
								node->pItems = itemToInsert;
								node->cBegin = itemToInsert->pID[cBeginIndex];
								node->pNext = pLinkedList;
								pLinkedListFront->pNext = node;
								return ppData;
							}


							pLinkedListFront = pLinkedListFront->pNext;
						}

						if (pSubItem != NULL)
						{
							pSubItem = pSubItem->pNext;
						}
						else if (pLinkedList != NULL)
						{
							pSubItem = (ITEM9*)pLinkedList->pItems;
						}
						if (!isFirstIteration)
						{
							pLinkedList = pLinkedList->pNext;
						}
						else
						{
							isFirstIteration = false;
						}
					}

				}

			}
		}
		cc++;
	}
	
	return ppData;
}

HEADER_A** RemoveItem(HEADER_A** ppData, char* pItemToRemove)
{
	HEADER_A** ppClone = &(*ppData); //clone so the original data won't get modified

	int cc2 = 0;
	int isEmpty = 0;
	while (cc2 < 26)
	{
		if (ppClone[cc2] == NULL)
		{
			isEmpty++;
		}
		cc2++;
	}
	try
	{
		if (isEmpty == 26) //if no data structure was inicialized throw an error and return
		{
			throw "Empty data structure!";
		}
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
		return ppData;
	}
	//checking if given item is formatted correctly
	int whiteSpaces = 0;
	for (int i = 0; i < strlen(pItemToRemove); i++)
	{
		int isSpcae = isspace(pItemToRemove[i]);
		if (isSpcae != 0)
		{
			whiteSpaces++;
			try
			{
				if (whiteSpaces > 1)
				{
					throw "Presented ID does not follow formatting rules!";
				}
			}
			catch (const char* e)
			{
				std::cout << "An error occured: " << e << std::endl;
				return ppData;
			}
		}
	}
	if (whiteSpaces == 0)
	{
		try
		{
			throw "Presented ID does not follow formatting rules!";
		}
		catch (const char* e)
		{
			std::cout << "An error occured: " << e << std::endl;
			return ppData;
		}
	}
	int cc = 0;
	ITEM9* itemToRemove = (ITEM9*)GetItem(9, pItemToRemove);
	while (cc < 26) //it is fixed that we have 26 pointers
	{

		HEADER_A* pLinkedList = ppClone[cc]; //pointer to move so original data won't get corrupted
		if (ppClone[cc] != NULL)
		{
			int linkedListCounter = 0;
			while (pLinkedList != NULL)//going through the list of items
			{
				ITEM9* pSubItem = (ITEM9*)pLinkedList->pItems;
				ITEM9* pSubItemTail = pSubItem;
				int subItemCounter = 0;
				bool isFirstIteration = true;
				while (pSubItem != NULL)//going through the list of sub items
				{

					if (strcmp(pSubItem->pID, itemToRemove->pID) == 0)
					{
						if (linkedListCounter == 0 && pLinkedList->pNext == NULL)
						{
							if (ppClone[cc]->pNext != NULL)
							{
								ppClone[cc]->pNext = ppClone[cc + 1];
							}

							delete[] pLinkedList;
							ppClone[cc] = NULL;
							return ppData;
						}
						if (subItemCounter == 0 && pLinkedList->pNext == NULL)
						{
							delete pSubItem;
							pLinkedList->pItems = NULL;
							pLinkedList->cBegin = NULL;
							
							return ppData;
						}
						else
						{

							if (pSubItem->pNext != NULL)
							{
								pLinkedList->pItems = pSubItem->pNext;
							}
							else
							{
								pLinkedList->pItems = NULL;
							}
							
							pSubItem->pNext = NULL;
							delete pSubItem;
							//pLinkedList->pItems = pSubItemTail;
							//pLinkedList = pLinkedList->pNext;
							return ppData;
						}
					}

					pSubItem = pSubItem->pNext;
					if (!isFirstIteration)
					{
						pSubItemTail = pSubItemTail->pNext;
					}
					isFirstIteration = false;
					subItemCounter++;
				}
					
				pLinkedList = pLinkedList->pNext;
				linkedListCounter++;
			}
		}
		cc++;
	}

	if (cc == 26)// item was not in the list
	{
		std::cout << "Specified data does not exist in the structure!" << std::endl;
		return ppData;
	}
}

/*int main()
{
	HEADER_A** ppData = GetStruct3(9,30); 
	//start of test coursework1
	PrintDataStructure(ppData);
	std::cout << "\n";
	InsertItem(ppData, (char*)"Z A");
	InsertItem(ppData, (char*)"Z Z");
	InsertItem(ppData, (char*)"Z K");
	InsertItem(ppData, (char*)"A Z");
	InsertItem(ppData, (char*)"A A");
	InsertItem(ppData, (char*)"A K");
	InsertItem(ppData, (char*)"G Z");
	InsertItem(ppData, (char*)"G A");
	InsertItem(ppData, (char*)"G K");
	InsertItem(ppData, (char*)"M A");
	InsertItem(ppData, (char*)"M Ba");
	InsertItem(ppData, (char*)"M Bb");
	InsertItem(ppData, (char*)"M Z");
	InsertItem(ppData, (char*)"M Bb");
	InsertItem(ppData, (char*)"Mba");
	PrintDataStructure(ppData);
	RemoveItem(ppData, (char*)"Z A");
	RemoveItem(ppData, (char*)"Z Z");
	RemoveItem(ppData, (char*)"Z K");
	RemoveItem(ppData, (char*)"A Z");
	RemoveItem(ppData, (char*)"A A");
	RemoveItem(ppData, (char*)"A K");
	RemoveItem(ppData, (char*)"G Z");
	RemoveItem(ppData, (char*)"G A");
	RemoveItem(ppData, (char*)"G K");
	RemoveItem(ppData, (char*)"M A");
	RemoveItem(ppData, (char*)"M Ba");
	RemoveItem(ppData, (char*)"M Bb");
	RemoveItem(ppData, (char*)"M Z");
	RemoveItem(ppData, (char*)"M Bb");
	RemoveItem(ppData, (char*)"Mba");
	std::cout << "\n";
	PrintDataStructure(ppData);
	//end of test coursework1
}*/