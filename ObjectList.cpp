#include "ObjectList.h"

battleCity::ObjectList::ObjectList() {}

battleCity::ObjectList::ObjectList(int i) : i(i) {}

int battleCity::ObjectList::insert(Object* objectPtr)
{
	try
	{
		objectPtrList.push_back(objectPtr);
		
	}
	catch (...)
	{
		cout << "Object insert error" << endl;
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
		for (unsigned long long i = 1; i < objectPtr->getSprite().size(); i++)
		{
			destroySprite(objectPtr->getSprite()[i]);
			objectPtr->getSprite()[i] = NULL;
		}
		objectPtr->getSprite()[0] = NULL;
		if(!objectPtr->objectIsDeleted())
			delete objectPtr;
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

vector<battleCity::Object*>& battleCity::ObjectList::getList()
{
	return objectPtrList;
}

int battleCity::ObjectList::getSize()
{
	return objectPtrList.size();
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
#if DEBUG == 2
	std::cout << "ObjectList Destructor" << std::endl;
	cout << endl;
#endif
	objectPtrList.clear();
	objectPtrList.shrink_to_fit();
}