#include "PCHeader.h"
#include "List.h"

namespace BattleCity
{
	template <typename T>
	List<T>::List()
	{
		
	}

	template<typename T>
	typename List<T>::Range List<T>::GetRange() const
	{
		return { mList.begin(), mList.end() };
	}

	template<typename T>
	T& List<T>::GetT(int id) const
	{
		return mList.at(id);
	}

	template<typename T>
	void List<T>::Insert(T* objPtr)
	{
		mList.try_emplace(objPtr->ID, objPtr);
	}

	template<typename T>
	void List<T>::Remove(int objID)
	{
		mList.erase(objID);
	}

	template<typename T>
	size_t List<T>::GetSize() const
	{
		return mList.size();
	}

	template<typename T>
	bool List<T>::IsEmpty() const
	{
		return GetSize() == 0;
	}

	template<typename T>
	void List<T>::Clear()
	{
		mList.clear();
	}
}
