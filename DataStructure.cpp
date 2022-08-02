#include "DataStructure.h"
#pragma warning (disable:4996)
HEADER_A* pFullCopyHeader(const HEADER_A& a)
{
	HEADER_A* copyOfOriginal = new HEADER_A(a);
	return copyOfOriginal;
}

HEADER_A** ppFullCopyHeader(HEADER_A* &a)
{
	HEADER_A** copyOfOriginal = new HEADER_A*(a);
	return copyOfOriginal;
}

DataStructure::DataStructure(const DataStructure& Original)
{
	for (int i = 0; i < 26; i++)
	{
		HEADER_A* a = *Original.ppData;
		if (a[i].pNext != NULL)
		{
			HEADER_A* innerList = a;
			ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
			ITEM9* pHead = pItemList;
			bool isFirst = true;
			while (innerList != NULL)
			{

				while (pItemList != NULL)
				{
					this->ppData = InsertItem(this->ppData,pItemList);
					pItemList = pItemList->pNext;
					if (!isFirst)
					{
						pHead = pHead->pNext;
					}
					isFirst = false;
				}

				innerList = innerList->pNext;
			}

		}

	}
	
}

std::ostream& operator<<(std::ostream& ostr, const DataStructure& str)
{
	if (str.ppData)
	{
		HEADER_A* a = *(str.ppData);

		for (int i = 0; i < 26; i++)
		{
			if (a[i].pNext != 0)
			{
				HEADER_A* innerList = a;
				ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
				while (innerList != NULL)
				{

					while (pItemList != NULL)
					{
						DATE3* pDate = pItemList->pDate;
						ostr << pItemList->pID << " " << pItemList->Code << " " << pDate->Day << " " << pDate->pMonth << " " << pDate->Year << std::endl;
						pItemList = pItemList->pNext;
					}

					innerList = innerList->pNext;
				}
			}
		}
	}
	return ostr;
}

int DataStructure::operator==(DataStructure& Other)
{
	for (int i = 0; i < 26; i++)
	{
		HEADER_A* a = *Other.ppData;
		HEADER_A* b = *this->ppData;
		if (a[i].pNext != NULL)
		{
			HEADER_A* innerList = a;
			ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
			ITEM9* pHead = pItemList;
			HEADER_A* innerListB = b;
			ITEM9* pItemListB = (ITEM9*)(b[i].pNext)->pItems;
			ITEM9* pHeadB = pItemListB;
			bool isFirst = true;
			while (innerList != NULL && innerListB != NULL)
			{
				while (pItemList != NULL && pItemListB != NULL)
				{
					if (strcmp(pItemList->pID,pItemListB->pID) != 0)
					{
						return 0;
					}
					if (!isFirst)
					{
						if (pHead != NULL)
						{
							pHead = pHead->pNext;
						}
						if (pHeadB != NULL)
						{
							pHeadB = pHeadB->pNext;
						}
					}
					isFirst = false;
					pItemList = pItemList->pNext;
					pItemListB = pItemListB->pNext;
				}
				

				innerList = innerList->pNext;
				innerListB = innerListB->pNext;
			}

		}

	}
	return 1;
}

DataStructure& DataStructure::operator=(const DataStructure& Right)
{
	return *new DataStructure(Right); //invites copy constructor
}

void DataStructure::Write(char* pFilename)
{
	std::ofstream file (pFilename);

	if (file.is_open())
	{
		for (int i = 0; i < 26; i++)
		{
			HEADER_A* a = *this->ppData;
			if (a[i].pNext != NULL)
			{
				HEADER_A* innerList = a;
				ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
				ITEM9* pHead = pItemList;
				bool isFirst = true;
				while (innerList != NULL)
				{
					while (pItemList != NULL)
					{
						file << pItemList->pID << std::endl;

						if (!isFirst)
						{
							if (pHead != NULL)
							{
								pHead = pHead->pNext;
							}
						}
						isFirst = false;
						pItemList = pItemList->pNext;
					}

					innerList = innerList->pNext;
				}

			}

		}

		file.close();
	}
	else
	{
		try
		{
			throw "Unable to open file!";
		}
		catch (const char* e)
		{
			std::cout << "An error occured: " << e << std::endl;
		}
	}
}

ITEM9* DataStructure::GetItems(char* pID)
{
	int whiteSpaces = 0;
	for (int i = 0; i < strlen(pID); i++)
	{
		int isSpcae = isspace(pID[i]);
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
				return 0;
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
			return 0;
		}
	}
	int cBeginIndex = 0;
	for (int i = 0; i < strlen(pID); i++) //calculating beginning of second word
	{
		if ((int)(pID[i]) == 32)
		{
			cBeginIndex = i + 1;
		}
	}
	HEADER_A** ppClone = this->ppData; //clone so the original data won't get modified
	HEADER_A* a = *ppClone;
	for (int i = 0; i < 26; i++)
	{
		if (a[i].pNext != NULL)
		{
			HEADER_A* innerList = a;
			ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
			ITEM9* pHead = pItemList;
			bool isFirst = true;
			while (innerList != NULL)
			{

				while (pItemList != NULL)
				{
					//std::cout << pItemList->pID << std::endl;
					if (strcmp(pItemList->pID, pID) == 0)
					{
						return pItemList;
					}
					pItemList = pItemList->pNext;
					if (!isFirst)
					{
						pHead = pHead->pNext;
					}
					isFirst = false;
				}

				innerList = innerList->pNext;
			}

		}

	}
	return 0;
}

HEADER_A** DataStructure::InsertItem(HEADER_A** ppData, ITEM9* pNewItem)
{
	HEADER_A** ppClone = ppData; //clone so the original data won't get modified
	if (pNewItem == NULL)
	{
		return ppData;
	}
	//checking if given item is formatted correctly
	int whiteSpaces = 0;
	for (int i = 0; i < strlen(pNewItem->pID); i++)
	{
		int isSpcae = isspace(pNewItem->pID[i]);
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
	
	ITEM9* itemToInsert = pNewItem;
	
	int cBeginIndex = 0;
	for (int i = 0; i < strlen(itemToInsert->pID); i++) //calculating beginning of second word
	{
		if ((int)(itemToInsert->pID[i]) == 32)
		{
			cBeginIndex = i + 1;
		}
	}
	int position = (int)itemToInsert->pID[0] - 65;
	
	if (!ppClone)
	{
		HEADER_A** ppHeader = new HEADER_A*;
		HEADER_A* pNewNode = new HEADER_A[26];
		HEADER_A* head = pNewNode;
		ppHeader = &head;
		for (int i = 0; i < 26; i++)
		{
			pNewNode[i].cBegin = 0;
			pNewNode[i].pItems = 0;
			pNewNode[i].pNext = 0;

		}
		pNewNode[position].pNext = new HEADER_A;
		//(pNewNode[position].pNext)->pNext = new HEADER_A;
		(pNewNode[position].pNext)->cBegin = itemToInsert->pID[cBeginIndex];
		(pNewNode[position].pNext)->pItems = itemToInsert;
		(pNewNode[position].pNext)->pNext = 0;
		ppData = ppFullCopyHeader(*ppHeader);
		return ppData;
	}
	//ppData exists
	HEADER_A** ppHeader = ppFullCopyHeader(*ppData); //full copy of original ppData
	HEADER_A* pNewNode = *ppHeader; //points to ppData[0][0]
	HEADER_A* head = pNewNode; //pointer to the start of the array (matrix)
			if (pNewNode[position].pNext == 0) // no item and header in given position
			{
				pNewNode[position].pNext = new HEADER_A;
				(pNewNode[position].pNext)->cBegin = itemToInsert->pID[cBeginIndex];
				(pNewNode[position].pNext)->pItems = itemToInsert;
				(pNewNode[position].pNext)->pNext = NULL;
			}
			else //header exists at position
			{
				HEADER_A* pLinkedList = pNewNode[position].pNext;
				HEADER_A* pHeadOfList = pLinkedList;
				bool isFirstIteration = false;
				int listPosition = (int)(pNewNode[position].pNext)->cBegin - (int)itemToInsert->pID[cBeginIndex];

				if (listPosition > 0) // iserts item to header if it is less then the current char, overwrites some values, look at words starting with A
				{
					while (pLinkedList != NULL)
					{

						if (listPosition >= 0)
						{
							pHeadOfList->cBegin = itemToInsert->pID[cBeginIndex];
							ITEM9* pItemList = (ITEM9*)pHeadOfList->pItems;
							itemToInsert->pNext = pItemList;
							pHeadOfList->pItems = itemToInsert;
						}
						
						
						listPosition = (int)pLinkedList->cBegin - (int)itemToInsert->pID[cBeginIndex];
						pLinkedList = pLinkedList->pNext;
						if (!isFirstIteration)
						{
							pHeadOfList = pHeadOfList->pNext;
						}
						isFirstIteration = true;
					}
				}
				else // insert item in the header if value is greater then current char
				{
					while (pLinkedList != NULL)
					{
						pLinkedList = pLinkedList->pNext;
					}
					if (pLinkedList == NULL)
					{
						pLinkedList = new HEADER_A;
						pLinkedList->pItems = itemToInsert;
						pLinkedList->cBegin = itemToInsert->pID[cBeginIndex];
						pLinkedList->pNext = NULL;
						((ITEM9*)((pNewNode[position].pNext)->pItems))->pNext = (ITEM9*)pLinkedList->pItems;
					}
				}
				
			}
	ppData = ppFullCopyHeader(*ppHeader);
	
	return ppData;
}

HEADER_A** DataStructure::RemoveItem(HEADER_A** ppData, char* pItemToRemove)
{
	HEADER_A** ppClone = &(*ppData); //clone so the original data won't get modified
	HEADER_A* a = *ppClone;
	for (int i = 0; i < 26; i++)
	{
		if(a[i].pNext != NULL)
		{
			HEADER_A* innerList = a;
			ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
			ITEM9* pHead = pItemList;
			bool isFirst = true;
			while (innerList != NULL)
			{

				while (pItemList != NULL)
				{
					//std::cout << pItemList->pID << std::endl;
					if (strcmp(pItemList->pID,pItemToRemove) == 0)
					{
						pHead = pItemList->pNext;
						(a[i].pNext)->pItems = pHead;
						ppData = ppFullCopyHeader(a);
						return ppData;
					}
					pItemList = pItemList->pNext;
					if (!isFirst)
					{
						pHead = pHead->pNext;
					}
					isFirst = false;
				}

				innerList = innerList->pNext;
			}

		}

	}

	try
	{
		throw "Item not found!";
	}
	catch (const char* e)
	{
		std::cout << "An error occured: " << e << std::endl;
		return ppData;
	}

}

void DataStructure::operator+=(ITEM9* pNewItem)
{
	HEADER_A** newList = InsertItem(this->ppData, pNewItem);
	this->ppData = newList;
}

void DataStructure::operator-=(char* pID)
{
	this->ppData = RemoveItem(DataStructure::ppData, pID);
}


DataStructure::DataStructure()
{
	this->ppData = 0;
}

DataStructure::DataStructure(char* pFileName)
{
	std::ifstream file(pFileName);
	this->ppData = 0;
	if (file.is_open())
	{
		std::string inputFromFile;
		int cc = 0;
		while (std::getline(file,inputFromFile))
		{
			for (int i = 0; i < strlen(inputFromFile.c_str()); i++)
			{
				cc++;
			}
			char* insert = new char[cc];
			strcpy(insert, inputFromFile.c_str());
			this->ppData = InsertItem(this->ppData, (ITEM9*)GetItem(9, insert));
		}
		file.close();
	}
	else
	{
		try
		{
			throw "File could not be opened!";
		}
		catch (const char* e)
		{
			std::cout << "An error occured: " << e << std::endl;
		}
	}
}

DataStructure::~DataStructure()
{
	if (!this->ppData)
	{
		delete this->ppData;
	}
	else
	{
		delete[] this->ppData;
	}
}

int DataStructure::GetItemsNumber()
{
	int itemsNumber = 0;
	if (!this->ppData)
	{
		return itemsNumber;
	}
	HEADER_A* a = *(this->ppData);
	for (int i = 0; i < 26; i++)
	{
		if (a[i].pNext != 0)
		{
			HEADER_A* innerList = a;
			ITEM9* pItemList = (ITEM9*)(a[i].pNext)->pItems;
			while (innerList != NULL)
			{
				while (pItemList != NULL)
				{
					itemsNumber++;
					pItemList = pItemList->pNext;
				}

				innerList = innerList->pNext;
			}
		}
	}
	return itemsNumber;
}



int main()
{
	//start of test coursework2
	char test1[] = "Banana Mania";
	char test2[] = "Persian Green";
	char test3[] = "Vegas Gold";
	char test4[] = "X X";
	char filename[] = "coursework2.txt";

	DataStructure* pds = new DataStructure(); //task 1

	for (int i = 0; i < 10; i++) //task 2
	{
		ITEM9* item = (ITEM9*)GetItem(9);
		*pds += item;
	}

	std::cout << *pds << std::endl; //task 3

	std::cout << pds->GetItemsNumber() << std::endl; //task 4
	std::cout << std::endl;
	std::cout << pds->GetItems(test1) << std::endl; //task 5


	std::cout << "Non existing element:" << std::endl;
	std::cout << pds->GetItems(test4) << std::endl; //task 6
	std::cout << std::endl;

	DataStructure* pdsCopy = new DataStructure(*pds); // task 7
	std::cout << "Copied data structure:" << std::endl;
	std::cout << *pdsCopy << std::endl;

	std::cout << "\n";
	pds->Write(filename); //task 8

	*pds -= test1; //task 9
	*pds -= test2;
	*pds -= test3;
	std::cout << "Minus 3 elements:" << std::endl;
	std::cout << *pds << std::endl;



	std::cout << (*pds == *pdsCopy) << std::endl; // task 10
	std::cout << std::endl;


	DataStructure* pds2 = new DataStructure(filename); // task 11
	std::cout << "Constructed from file:" << std::endl;
	std::cout << *pds2 << std::endl;
	std::cout << std::endl;

	pds2 = pds; // task 12
	std::cout << "Equal operator:" << std::endl;
	std::cout << *pds2 << std::endl;
	//end of test coursework2
}