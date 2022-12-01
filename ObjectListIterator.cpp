#include "ObjectListIterator.h"

#include <iostream>

//Constructor
battleCity::ObjectListIterator::ObjectListIterator(const ObjectList* list) : managerPtrlist(list)
{
	list = nullptr;
	this->first();
}


void battleCity::ObjectListIterator::first()
{
	this->itList = managerPtrlist->mObjectPtrList.begin();
}

void battleCity::ObjectListIterator::last()
{
	this->itList = managerPtrlist->mObjectPtrList.end() - 1;
}

void battleCity::ObjectListIterator::next()
{
	if(this->itList < managerPtrlist->mObjectPtrList.end())
		++(this->itList);
}

bool battleCity::ObjectListIterator::isDone() const
{
	return this->itList == managerPtrlist->mObjectPtrList.end();
}

std::vector<battleCity::Object*>::const_iterator battleCity::ObjectListIterator::currentObject() const
{
	return this->itList;
}

void battleCity::ObjectListIterator::setList(const ObjectList* p_list)
{
	managerPtrlist = p_list;
}
