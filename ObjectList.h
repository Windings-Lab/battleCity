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
		/// Count of objects in list
		int count;
		/// Vector of pointers to objects
		vector<shared_ptr<Object>> objectPtrList;
	public:

		friend class ObjectListIterator;
		ObjectList();
		~ObjectList();

		int insert(shared_ptr<Object> objectPtr);
		int remove(shared_ptr<Object> objectPtr);
		void clear();
	};
}
