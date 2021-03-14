#pragma once

#include <vector>

#include "Object.h"
#include "ObjectList.h"

namespace battleCity
{
	class Object;
	class ObjectList;

	class ObjectListIterator
	{
	private:
		/// Iterator must be given list when created
		ObjectListIterator();
		/// List iterating over
		const ObjectList* managerPtrlist;
		std::vector<Object*>::const_iterator itList;
	public:

		/// Create iterator, over indicated list
		ObjectListIterator(const ObjectList* ptrList);

		/// Set iterator to first item in list
		void first();

		/// Reset to last object in list
		void last();

		/// Set iterator to next item in list
		void next();

		/// Return true if at end of list
		bool isDone() const;

		/// Return iterator pointer to current item in list
		std::vector<Object*>::const_iterator currentObject() const;

		ObjectListIterator& operator=(const ObjectListIterator& rhs);

		/// Set to new List
		void setList(const ObjectList* p_list);
	};
}

