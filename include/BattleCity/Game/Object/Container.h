#pragma once

#include "BattleCity/Game/Object/Aliases.h"

namespace BattleCity::Game::Object
{
	class Object;

	using ObjectContainer = std::vector<std::unique_ptr<Object>>;

	class Container
	{
	private:
		using ObjectIndex = int;
		using IDHashMap = std::unordered_map<ObjectID, ObjectIndex>;

	private:
		friend void swap(Container&, Container&) noexcept;

	public:
		Container() = default;

		DISALLOW_COPY(Container)

		Container(Container&& mve) noexcept;
		Container& operator=(Container&& rhs) noexcept;

		~Container();

		Object& GetObject(int id) const;

		void Insert(std::unique_ptr<Object>&& objPtr);
		void Remove(int objID);

		int GetSize() const noexcept;
		bool IsEmpty() const noexcept;

		void Clear() noexcept;

		ObjectContainer::const_iterator begin() const noexcept;
		ObjectContainer::const_iterator end() const noexcept;

	private:
		ObjectContainer mContainer;
		IDHashMap mHashMap;
	};
}
