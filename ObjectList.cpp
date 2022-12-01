#include "ObjectList.h"
#include "Object.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

namespace battleCity
{
	ObjectList::ObjectList() : ObjectList(0)
	{
		mObjectPtrList.reserve(100);
	}

	ObjectList::ObjectList(int index) : mID(index)
	{
		
	}

	ObjectList::ObjectList(ObjectList&& mve) noexcept : ObjectList(mve.mID)
	{
		swap(*this, mve);
	}

	int ObjectList::Insert(const std::weak_ptr<Object> objectPtr)
	{
		try
		{
			mObjectPtrList.push_back(objectPtr.lock());
		}
		catch (...)
		{
			std::cout << "Object insert error" << std::endl;
			return -1;
		}

		return 0;
	}

	int ObjectList::Remove(const std::weak_ptr<Object> objectPtr)
	{
		if (const auto it = std::find_if(mObjectPtrList.begin(), mObjectPtrList.end(),
			[&objectPtr](const std::shared_ptr<Object>& ptr)
			{ return ptr == objectPtr.lock(); }); it != mObjectPtrList.end())
		{
			mObjectPtrList.erase(it);
		}
		else
		{
			return -1;
		}

		return 0;
	}

	int ObjectList::RemoveByWorldId(int objID)
	{
		if (const auto it = std::lower_bound(mObjectPtrList.begin(), mObjectPtrList.end(), objID,
			[](const std::shared_ptr<Object>& obj, int id)
			{
				return obj->worldID < id;
			}); it != mObjectPtrList.end())
		{
			mObjectPtrList.erase(it);
		}
		else
		{
			return -1;
		}
		return 0;
	}

	int ObjectList::RemoveByMoveId(int objID)
	{
		if (const auto it = std::lower_bound(mObjectPtrList.begin(), mObjectPtrList.end(), objID,
			[](const std::shared_ptr<Object>& obj, int id)
			{
				return obj->moveID < id;
			}); it != mObjectPtrList.end())
		{
			mObjectPtrList.erase(it);
		}
		else
		{
			return -1;
		}
		return 0;
	}

	size_t ObjectList::GetSize() const
	{
		return mObjectPtrList.size();
	}

	bool ObjectList::IsEmpty() const
	{
		return GetSize() == 0;
	}

	void ObjectList::Clear()
	{
		mObjectPtrList.clear();
		mObjectPtrList.shrink_to_fit();
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

		swap(first.mID, second.mID);
		swap(first.mObjectPtrList, second.mObjectPtrList);
	}
}