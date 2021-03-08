#pragma once

#include "headers.h"
#include "Object.h"
#include "ObjectListIterator.h"

namespace battleCity
{
	class ObjectListIterator;

	class ObjectList
	{
	private:
		/// Vector of pointers to objects
		vector<Object*> objectPtrList;
		int i;
	public:

		friend class ObjectListIterator;
		ObjectList();
		ObjectList(int i);
		~ObjectList();

		int insert(Object* objectPtr);
		int remove(Object* objectPtr);
		vector<Object*>& getList();
		int getSize();
		void clear();
	};
}
