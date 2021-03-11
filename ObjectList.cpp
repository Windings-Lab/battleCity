#include "ObjectList.h"
#include "Object.h"
#include "ObjectListIterator.h"

#include <iostream>
#include <algorithm>
#include <vector>

battleCity::ObjectList::ObjectList() : i(0)
{}

battleCity::ObjectList::ObjectList(int index) : i(index) {}

int battleCity::ObjectList::insert(Object* objectPtr)
{
	try
	{
		objectPtrList.push_back(objectPtr);
	}
	catch (...)
	{
		std::cout << "Object insert error" << std::endl;
		return -1;
	}
	objectPtr = NULL;
	return 0;
}

int battleCity::ObjectList::remove(Object* objectPtr)
{
	auto it = std::find(objectPtrList.begin(), objectPtrList.end(), objectPtr);
	if (it != objectPtrList.end())
	{
		*it = NULL;
		objectPtrList.erase(it);
	}
	else
	{
		return -1;
	}
	objectPtr = NULL;
	return 0;
}

std::vector<battleCity::Object*>& battleCity::ObjectList::getList()
{
	return objectPtrList;
}

int battleCity::ObjectList::getSize()
{
	return objectPtrList.size();
}

bool battleCity::ObjectList::isEmpty()
{
	return getSize() == 0;
}

void battleCity::ObjectList::clear()
{
	for (unsigned int i = 0; i < objectPtrList.size(); i++)
	{
		objectPtrList[i] = NULL;
	}
	objectPtrList.clear();
	objectPtrList.shrink_to_fit();
}


battleCity::ObjectList::~ObjectList()
{
	objectPtrList.clear();
	objectPtrList.shrink_to_fit();
}