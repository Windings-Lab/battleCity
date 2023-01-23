#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object
{
	class Object;

	using ObjectContainer = std::vector<std::shared_ptr<Object>>;

	class Container
	{
	private:
		using ObjectIndex = int;
		using IDHashMap = std::unordered_map<ID, ObjectIndex>;

	private:
		friend void swap(Container&, Container&) noexcept;

	public:
		Container() = default;

		DISALLOW_COPY(Container)

		Container(Container&& mve) noexcept;
		Container& operator=(Container&& rhs) noexcept;

		~Container();

		std::shared_ptr<Object> GetObject(int id) const;

		void Insert(std::shared_ptr<Object>&& objPtr);
		void RemoveBy(int objID);

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
