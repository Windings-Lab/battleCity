#pragma once

#include "BattleCity/Game/World/Object/ObjectContainer.h"
#include "Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Engine::Texture
{
	class GroupLibrary;
}

namespace BattleCity::Game::World
{
	using Relative = Vector2Int;

	class Level;

	class Map final
	{
	public:
		explicit Map(Relative, const Engine::Texture::GroupLibrary&);

		DISALLOW_COPY_MOVE(Map)

		~Map() = default;

		void SetWorldRelative(const World::Relative&) noexcept;
		const World::Relative& GetWorldRelative() const noexcept;

		// Returns object that can be controlled with user Input
		std::shared_ptr<Object::Object> CreateMap(const Level&);

		std::shared_ptr<Object::Object> GetObjectBy(Object::ID) const;
		void InsertObject(std::shared_ptr<Object::Object>, Object::Layer = Object::Layer::Front);
		void MarkForDelete(Object::ID);

		const Object::Container& GetLayer(Object::Layer) const;

	private:
		Object::Factory::Standart mObjectFactory;
		World::Relative mWorldRelative;

		Object::Container mBackLayer;
		Object::Container mFrontLayer;
		Object::Container mUILayer;
	};
}
