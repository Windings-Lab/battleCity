#include "PCHeader.h"

#include "ObjectList.h"
#include "Object.h"

namespace BattleCity::Object
{
	ObjectList::ObjectList() : mList(100)
	{
	}

	ObjectList::ObjectList(ObjectList&& mve) noexcept : ObjectList()
	{
		swap(*this, mve);
	}

	ObjectList::Range ObjectList::GetRange() const
	{
		return Range {mList.begin(), mList.end()};
	}

	Object& ObjectList::GetObject(int id) const
	{
		return *mList.at(id).get();
	}

	void ObjectList::Insert(Object* objPtr)
	{
		mList.try_emplace(objPtr->ID, objPtr);
	}

	void ObjectList::Remove(int objID)
	{
		mList.erase(objID);
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
