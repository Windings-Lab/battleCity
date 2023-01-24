#include "PCHeader.h"
#include "ObjectContainer.h"

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	Container::Container(Container&& mve) noexcept : Container()
	{
		swap(*this, mve);
	}

	Container& Container::operator=(Container&& rhs) noexcept
	{
		Container temp(std::move(rhs));
		swap(*this, temp);
		return *this;
	}

	Container::~Container() = default;

	std::shared_ptr<Object> Container::GetObject(int id) const
	{
		int index = mHashMap.at(id);
		return mContainer[index];
	}

	void Container::Insert(std::shared_ptr<Object>&& objPtr)
	{
		mHashMap.try_emplace(objPtr->GetID(), GetSize());
		mContainer.emplace_back(std::move(objPtr));
	}

	void Container::RemoveBy(int objID)
	{
		const ObjectIndex index = mHashMap.at(objID);
		const ID backID = mContainer.back()->GetID();
		if(mContainer[index] != mContainer.back())
		{
			mHashMap.at(backID) = index;
			mContainer[index] = std::move(mContainer.back());
		}

		mHashMap.erase(objID);
		mContainer.pop_back();
	}

	int Container::GetSize() const noexcept
	{
		return static_cast<int>(mContainer.size());
	}

	bool Container::IsEmpty() const noexcept
	{
		return GetSize() == 0;
	}

	void Container::Clear() noexcept
	{
		mHashMap.clear();
		mContainer.clear();
	}

	ObjectContainer::const_iterator Container::begin() const noexcept
	{
		return mContainer.cbegin();
	}

	ObjectContainer::const_iterator Container::end() const noexcept
	{
		return mContainer.cend();
	}

	const std::shared_ptr<Object>& Container::operator[](int index) const
	{
		return mContainer[index];
	}

	void swap(Container& first, Container& second) noexcept
	{
		first.mContainer.swap(second.mContainer);
		first.mHashMap.swap(second.mHashMap);
	}
}
