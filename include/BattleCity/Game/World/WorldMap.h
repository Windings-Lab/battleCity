#pragma once

#include "BattleCity/Game/World/Object/ObjectContainer.h"

namespace BattleCity::Engine::Texture
{
	class GroupLibrary;
}

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

		void SetWorldRelative(const TopLeft&) noexcept;
		const TopLeft& GetWorldRelative() const noexcept;

		void CreateMap(const Level&, const Engine::Texture::GroupLibrary&);

		Object::Object& GetObjectBy(Object::ID) const;
		Object::Object* InsertObject(std::unique_ptr<Object::Object>&&, Object::Layer = Object::Layer::Front);
		void MarkForDelete(Object::ID);

		const Object::Container& GetBackLayer() const noexcept;
		const Object::Container& GetFrontLayer() const noexcept;

	private:
		TopLeft mWorldRelative;

		Object::Container mBackLayer;
		Object::Container mFrontLayer;
	};
}
