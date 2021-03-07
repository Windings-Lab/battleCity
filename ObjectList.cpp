#include "ObjectList.h"

battleCity::ObjectList::ObjectList() : count(0)
{
	objectPtrList.reserve(0);
}

int battleCity::ObjectList::insert(shared_ptr<Object> objectPtr)
{
	try
	{
		objectPtrList.push_back(objectPtr);
		count++;
	}
	catch (...)
	{
		cout << "Object insert error" << endl;
		return -1;
	}
	return 0;
}

int battleCity::ObjectList::remove(shared_ptr<Object> objectPtr)
{
	auto it = std::find(objectPtrList.begin(), objectPtrList.end(), objectPtr);
	if (it != objectPtrList.end())
	{
		objectPtrList.erase(it);
		count--;
	}
	else
	{
		return -1;
	}
	return 0;
}

void battleCity::ObjectList::clear()
{
	for (unsigned int i = 0; i < objectPtrList.size(); i++)
	{
		objectPtrList[i].reset();
	}
	objectPtrList.clear();
	objectPtrList.shrink_to_fit();
}


battleCity::ObjectList::~ObjectList()
{
#if DEBUG == 2
	std::cout << "ObjectList Destructor" << std::endl;
	cout << endl;
#endif
	for (unsigned int i = 0; i < objectPtrList.size(); i++)
	{
		objectPtrList[i].reset();
		objectPtrList[i] = NULL;
	}
	objectPtrList.clear();
	objectPtrList.shrink_to_fit();
}