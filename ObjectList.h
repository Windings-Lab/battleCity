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

		int removeByWorldID(int objID);
		int removeByMoveID(int objID);

		std::vector<Object*>& getList();
		int getSize();

		// List is Empty?
		bool isEmpty();

		void clear();
	};
}
