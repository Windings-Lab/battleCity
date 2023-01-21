#include "PCHeader.h"

#include "Wall.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Wall::Wall() : Object()
	{
        AddComponent<Component::Texture>(*this);
        AddComponent<Component::Collider>(*this);
        AddComponent<Component::Movable>(*this);
	}

	void Wall::Update()
	{
        // If Health <= 0, destroy this
	}
	void Wall::ResolveCollisions(Object& other)
	{
		// Empty
	}
}
