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
		/// Vector of pointers to objects
		std::vector<std::shared_ptr<Object>> mObjectPtrList;
		int mID;

		friend void swap(ObjectList&, ObjectList&) noexcept;
	public:
		friend class ObjectListIterator;

		ObjectList();
		explicit ObjectList(int index);

		ObjectList(ObjectList& cpy) = delete;
		ObjectList(ObjectList&& mve) noexcept;

		~ObjectList() = default;

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
}
