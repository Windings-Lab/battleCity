#pragma once

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Game/World/Object/Containers/ObjectContainer.h"
#include "Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Engine::Physics
{
	class Rectangle;
}

namespace BattleCity::Engine::Texture
{
	class GroupLibrary;
}

namespace BattleCity::Game::World
{
	namespace Object
	{
		class QuadTree;
	}

	using Relative = Vector2Int;
	using Bounds = Engine::Physics::Rectangle;

	class Level;

	class Map final
	{
	public:
		explicit Map(const Engine::Texture::GroupLibrary&, Object::QuadTree&);

		DISALLOW_COPY_MOVE(Map)

		~Map() = default;

		// Returns object that can be controlled with user Input
		std::shared_ptr<Object::Object> CreateMap(const Level&);
		const Engine::Physics::Rectangle& GetBounds() const noexcept;

		std::shared_ptr<Object::Object> GetObjectBy(Object::ID, Object::Layer) const;
		void InsertObject(std::shared_ptr<Object::Object>, Object::Layer = Object::Layer::Middle);

		void MarkForDelete(Object::ID, Object::Layer);
		void DestroyObjects();

		const Object::Container& GetLayer(Object::Layer) const;
		Object::Container& GetDebugLayer();

	private:
		Bounds mBounds;
		Object::Factory::Standart mObjectFactory;

		std::vector<Object::Container> mContainers;

		std::unordered_set<Object::ID> mDeleterDuplicateCheck;
		std::vector<std::vector<Object::ID>> mDeleters;
	};
}
