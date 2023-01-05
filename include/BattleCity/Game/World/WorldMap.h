#pragma once

#include "BattleCity/Game/World/Object/ObjectContainer.h"

namespace BattleCity::Game::World
{
	using TopLeft = Vector2Int;

	class Level;

	class Map final
	{
	public:
		Map() = default;

		DISALLOW_COPY_MOVE(Map)

		~Map() = default;

		void SetWorldRelative(const TopLeft& worldRelative) noexcept;
		const TopLeft& GetWorldRelative() const noexcept;

		void CreateMap(const Level& level);

		Object::Object& GetObject(int id) const;
		Object::Object* InsertObject(std::unique_ptr<Object::Object>&& object, Object::Layer layer = Object::Layer::Front);
		void MarkForDelete(int objID);

		const Object::Container& GetBackLayer() const noexcept;
		const Object::Container& GetFrontLayer() const noexcept;

	private:
		TopLeft mWorldRelative;

		Object::Container mBackLayer;
		Object::Container mFrontLayer;
	};
}
