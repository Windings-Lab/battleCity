#pragma once

#include <unordered_map>
#include <memory>

#include "Object.h"

namespace battleCity
{
	class TankPlayer;
	class ObjectListIterator;
	class Object;

	class ObjectList
	{
	private:
		struct Range;

		std::unordered_map<int, std::unique_ptr<Object>> mList;

		friend void swap(ObjectList&, ObjectList&) noexcept;
	public:
		friend class ObjectListIterator;
		friend TankPlayer* GetPlayer(int id); // TODO: Temporary

		ObjectList();

		ObjectList(ObjectList& cpy) = delete;
		ObjectList(ObjectList&& mve) noexcept;

		~ObjectList() = default;

		Range GetRange() const;
		Object& GetObject(int id) const;

		int Insert(std::unique_ptr<Object>& objPtr);
		int Remove(int objID);

		size_t GetSize() const;
		bool IsEmpty() const;

		void Clear();

		ObjectList& operator=(const ObjectList& rhs) = delete;
		ObjectList& operator=(ObjectList&& rhs) noexcept;
	};

	struct ObjectList::Range
	{
		std::unordered_map<int, std::unique_ptr<Object>>::const_iterator Begin;
		std::unordered_map<int, std::unique_ptr<Object>>::const_iterator End;
		std::unordered_map<int, std::unique_ptr<Object>>::const_iterator begin() { return Begin; }
		std::unordered_map<int, std::unique_ptr<Object>>::const_iterator end() { return End; }
	};
}
