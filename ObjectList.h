#pragma once

#include <vector>

#include "Object.h"

namespace battleCity
{
	class ObjectListIterator;
	class Object;

	class ObjectList
	{
	private:
		/// Vector of pointers to objects
		std::vector<Object*> objectPtrList;
		int i;
	public:

		friend class ObjectListIterator;
		ObjectList();
		ObjectList(int index);
		~ObjectList();

		int insert(Object* objectPtr);
		int remove(Object* objectPtr);
		std::vector<Object*>& getList();
		int getSize();

		bool isEmpty();

		void clear();
	};
}
