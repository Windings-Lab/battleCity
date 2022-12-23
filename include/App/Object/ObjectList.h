#pragma once

namespace BattleCity::Object
{
	class Object;

	class ObjectList
	{
		struct Iterator
		{
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator Begin;
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator End;
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator begin() { return Begin; }
			std::unordered_map<int, std::unique_ptr<Object>>::const_iterator end() { return End; }
		};
	public:
		ObjectList();

		ObjectList(const ObjectList& cpy) = delete;
		ObjectList& operator=(const ObjectList& rhs) = delete;

		ObjectList(ObjectList&& mve) noexcept;
		ObjectList& operator=(ObjectList&& rhs) noexcept;

		~ObjectList() = default;

		Iterator GetIterator() const;
		Object& GetObject(int id) const;

		void Insert(std::unique_ptr<Object>&& objPtr);
		void Remove(int objID);

		size_t GetSize() const;
		bool IsEmpty() const;

		void Clear();


	private:
		std::unordered_map<int, std::unique_ptr<Object>> mList;

		friend void swap(ObjectList&, ObjectList&) noexcept;
	};
}
