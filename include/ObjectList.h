#pragma once

#include <memory>
#include <unordered_map>

#include "Object.h"

namespace BattleCity
{
	class ObjectList
	{
		struct Range
		{
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator Begin;
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator End;
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator begin() { return Begin; }
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator end() { return End; }
		};
	public:
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
	private:
		std::unordered_map<int, std::unique_ptr<Object>> mList;

		friend void swap(ObjectList&, ObjectList&) noexcept;
	};
}
