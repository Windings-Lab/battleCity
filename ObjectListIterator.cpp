#include "ObjectListIterator.h"

battleCity::ObjectListIterator::~ObjectListIterator()
{
#if DEBUG == 2
	std::cout << "ObjectListIterator Destructor" << std::endl;
#endif
}

battleCity::ObjectListIterator::ObjectListIterator(const shared_ptr<ObjectList>& list) 
	: managerPtrlist(list) {}

void battleCity::ObjectListIterator::first()
{
	this->itList = managerPtrlist->objectPtrList.begin();
}

void battleCity::ObjectListIterator::last()
{
	this->itList = managerPtrlist->objectPtrList.end() - 1;
}

void battleCity::ObjectListIterator::next()
{
	if(this->itList < managerPtrlist->objectPtrList.end())
		++(this->itList);
}

bool battleCity::ObjectListIterator::isDone() const
{
	return this->itList == managerPtrlist->objectPtrList.end();
}

vector<shared_ptr<battleCity::Object>>::const_iterator battleCity::ObjectListIterator::currentObject() const
{
	return this->itList;
}