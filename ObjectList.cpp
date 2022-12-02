#include "ObjectList.h"
#include "Object.h"

#include <iostream>
#include <utility>

namespace battleCity
{
	ObjectList::ObjectList()
	{
		mList.reserve(100);
	}

	ObjectList::ObjectList(ObjectList&& mve) noexcept : ObjectList()
	{
		swap(*this, mve);
	}

	ObjectList::Range ObjectList::GetRange() const
	{
		return Range {mList.begin(), mList.end()};
	}

	Object* const ObjectList::GetObject(int id) const
	{
		return mList.at(id).get();
	}

	int ObjectList::Insert(const std::unique_ptr<Object>& objPtr)
	{
		try
		{
			mList.try_emplace(objPtr->GetID(), std::move(objPtr));
		}
		catch (...)
		{
			std::cout << "Object insert error" << std::endl;
			return -1;
		}

		return 0;
	}

	int ObjectList::Remove(int objID)
	{
		return mList.erase(objID) != 0 ? 0 : -1;
	}

	size_t ObjectList::GetSize() const
	{
		return mList.size();
	}

	bool ObjectList::IsEmpty() const
	{
		return GetSize() == 0;
	}

	void ObjectList::Clear()
	{
		mList.clear();
	}

	ObjectList& ObjectList::operator=(ObjectList&& rhs) noexcept
	{
		ObjectList temp(std::move(rhs));
		swap(*this, temp);
		return *this;
	}

	void swap(ObjectList& first, ObjectList& second) noexcept
	{
		using std::swap;

		swap(first.mList, second.mList);
	}
}
