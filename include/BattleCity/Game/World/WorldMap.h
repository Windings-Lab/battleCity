#pragma once

#include "BattleCity/Game/World/Object/ObjectContainer.h"
#include "Object/Factory/ObjectFactoryStandart.h"

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
		explicit Map(const Engine::Texture::GroupLibrary&);

		DISALLOW_COPY_MOVE(Map)

		~Map() = default;

		void SetWorldRelative(const TopLeft&) noexcept;
		const TopLeft& GetWorldRelative() const noexcept;

		void CreateMap(const Level&);

		Object::Object& GetObjectBy(Object::ID) const;
		Object::Object* InsertObject(std::unique_ptr<Object::Object>&&, Object::Layer = Object::Layer::Front);
		void MarkForDelete(Object::ID);

		const Object::Container& GetBackLayer() const noexcept;
		const Object::Container& GetFrontLayer() const noexcept;

	private:
		Object::Factory::Standart mObjectFactory;
		TopLeft mWorldRelative;

		Object::Container mBackLayer;
		Object::Container mFrontLayer;
	};
}
