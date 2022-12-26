#include "PCHeader.h"

#include "ObjectContainer.h"
#include "Object.h"

namespace BattleCity::Object
{
	ObjectContainer::ObjectContainer(ObjectContainer&& mve) noexcept : ObjectContainer()
	{
		swap(*this, mve);
	}

	ObjectContainer& ObjectContainer::operator=(ObjectContainer&& rhs) noexcept
	{
		ObjectContainer temp(std::move(rhs));
		swap(*this, temp);
		return *this;
	}

	Object& ObjectContainer::GetObject(int id) const
	{
		return *mList[id];
	}

	void ObjectContainer::Insert(std::unique_ptr<Object>&& objPtr)
	{
		mIDMap.try_emplace(objPtr->GetID(), GetSize());
		mList.emplace_back(std::move(objPtr));
	}

	void ObjectContainer::Remove(int objID)
	{
		const ObjectVectorIndex index = mIDMap.at(objID);
		const ObjectID backID = mList.back()->GetID();
		if(mList[index] != mList.back())
		{
			mIDMap.at(backID) = index;
			mList[index] = std::move(mList.back());
		}

		mIDMap.erase(objID);
		mList.pop_back();
	}

	int ObjectContainer::GetSize() const noexcept
	{
		return static_cast<int>(mList.size());
	}

	bool ObjectContainer::IsEmpty() const noexcept
	{
		return GetSize() == 0;
	}

	void ObjectContainer::Clear() noexcept
	{
		mIDMap.clear();
		mList.clear();
	}

	ObjectVector::const_iterator ObjectContainer::begin() const noexcept
	{
		return mList.cbegin();
	}

	ObjectVector::const_iterator ObjectContainer::end() const noexcept
	{
		return mList.cend();
	}

	void swap(ObjectContainer& first, ObjectContainer& second) noexcept
	{
		first.mList.swap(second.mList);
		first.mIDMap.swap(second.mIDMap);
	}
}
