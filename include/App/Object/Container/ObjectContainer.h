#pragma once

#include "Object.h"

namespace BattleCity::Object
{
	using ObjectVector = std::vector<std::unique_ptr<Object>>;

	class ObjectContainer
	{
	public:
		ObjectContainer() = default;

		DISALLOW_COPY(ObjectContainer)

		ObjectContainer(ObjectContainer&& mve) noexcept;
		ObjectContainer& operator=(ObjectContainer&& rhs) noexcept;

		~ObjectContainer() = default;

		Object& GetObject(int id) const;

		void Insert(std::unique_ptr<Object>&& objPtr);
		void Remove(int objID);

		int GetSize() const noexcept;
		bool IsEmpty() const noexcept;

		void Clear() noexcept;

		ObjectVector::const_iterator begin() const noexcept;
		ObjectVector::const_iterator end() const noexcept;

	private:
		using ObjectVectorIndex = int;
		using ObjectID			= int;
		using IDHashMap = std::unordered_map<ObjectID, ObjectVectorIndex>;

		ObjectVector mList;
		IDHashMap mIDMap;

		friend void swap(ObjectContainer&, ObjectContainer&) noexcept;
	};
}
