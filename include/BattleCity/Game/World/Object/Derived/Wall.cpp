#include "PCHeader.h"

#include "Wall.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Wall::Wall()
		: Object()
		, mHealth(AddComponent<Component::Health>(*this))
	{
        AddComponent<Component::Texture>(*this);
        AddComponent<Component::Collider>(*this);
	}

	void Wall::Update()
	{
		if(mHealth->GetHealth() <= 0)
		{
			MarkForDestroy();
		}
	}
	void Wall::ResolveCollisions(Object& other)
	{
		// Empty
	}
	void Wall::OnOutOfBounds(const Vector2Int&)
	{
		// Empty
	}
}
