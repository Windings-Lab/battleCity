#pragma once

#include <vector>
#include <memory>

#include "Object.h"

namespace battleCity
{
	class ObjectListIterator;
	class Object;

	class ObjectList
	{
	private:
		struct Range;

		std::vector<std::shared_ptr<Object>> mObjectPtrList;

		friend void swap(ObjectList&, ObjectList&) noexcept;
	public:
		friend class ObjectListIterator;

		ObjectList();

		ObjectList(ObjectList& cpy) = delete;
		ObjectList(ObjectList&& mve) noexcept;

		~ObjectList() = default;

		Range GetRange() const;

		int Insert(const std::weak_ptr<Object> objectPtr);
		int Remove(const std::weak_ptr<Object> objectPtr);

		int RemoveByWorldId(int objID);
		int RemoveByMoveId(int objID);

		size_t GetSize() const;
		bool IsEmpty() const;

		void Clear();

		ObjectList& operator=(const ObjectList& rhs) = delete;
		ObjectList& operator=(ObjectList&& rhs) noexcept;
	};

	struct ObjectList::Range
	{
		std::vector<std::shared_ptr<Object>>::const_iterator Begin;
		std::vector<std::shared_ptr<Object>>::const_iterator End;
		std::vector<std::shared_ptr<Object>>::const_iterator begin() { return Begin; }
		std::vector<std::shared_ptr<Object>>::const_iterator end() { return End; }
	};
}
