#pragma once
#include "Object.h"
#include "ObjectList.h"

namespace battleCity
{
	class ObjectList;

	class ObjectListIterator
	{
	private:
		/// Iterator must be given list when created
		ObjectListIterator();
		/// List iterating over
		const shared_ptr<ObjectList>& managerPtrlist;
		vector<shared_ptr<Object>>::const_iterator itList;
	public:
		~ObjectListIterator();

		/// Create iterator, over indicated list
		ObjectListIterator(const shared_ptr<ObjectList>& ptrList);

		/// Set iterator to first item in list
		void first();

		/// Reset to last object in list
		void last();

		/// Set iterator to next item in list
		void next();

		/// Return true if at end of list
		bool isDone() const;

		/// Return pointer to current item in list, NULL if done/empty
		vector<shared_ptr<Object>>::const_iterator currentObject() const;

		ObjectListIterator& operator=(const ObjectListIterator& rhs);

		/// Set to new List
		void setList(const shared_ptr<ObjectList> p_list);
	};
}

