#pragma once

namespace BattleCity
{
	template<typename T>
	class List
	{
		struct Range
		{
			std::unordered_map<int, std::unique_ptr<T>>::const_iterator Begin;
			std::unordered_map<int, std::unique_ptr<T>>::const_iterator End;
			std::unordered_map<int, std::unique_ptr<T>>::const_iterator begin() { return Begin; }
			std::unordered_map<int, std::unique_ptr<T>>::const_iterator end() { return End; }
		};
	public:
		List();

		List<T>& operator=(const List& rhs) = delete;
		List(const List& cpy) = delete;

		List(List&& mve) noexcept = default;
		List<T>& operator=(List&& rhs) noexcept = default;

		~List() = default;

		Range GetRange() const;
		T& GetT(int id) const;

		void Insert(T* objPtr);
		void Remove(int objID);

		size_t GetSize() const;
		bool IsEmpty() const;

		void Clear();
	private:
		std::unordered_map<int, std::unique_ptr<T>> mList;
	};
}
