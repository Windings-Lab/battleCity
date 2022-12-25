#include "PCHeader.h"

#include "ObjectList.h"
#include "Object.h"

namespace BattleCity::Object
{
	ObjectList::ObjectList() : mList(100), mIt({ mList.begin(), mList.end() })
	{
	}

	ObjectList::ObjectList(ObjectList&& mve) noexcept : ObjectList()
	{
		swap(*this, mve);
	}

	ObjectList::Iterator& ObjectList::GetIterator()
	{
		return mIt;
	}

	Object& ObjectList::GetObject(int id) const
	{
		return *mList.at(id).get();
	}

	void ObjectList::Insert(std::unique_ptr<Object>&& objPtr)
	{
		mList.try_emplace(objPtr->GetID(), std::move(objPtr));
		mIt = { mList.begin(), mList.end() };
	}

	void ObjectList::Remove(int objID)
	{
		mList.erase(objID);
		mIt = { mList.begin(), mList.end() };
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
		mIt = { mList.begin(), mList.end() };
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
		swap(first.mIt, second.mIt);
	}
}
