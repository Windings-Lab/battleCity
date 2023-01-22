#include "PCHeader.h"

#include "Phoenix.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Phoenix::Phoenix() : Object()
	{
        AddComponent<Component::Texture>(*this);
        AddComponent<Component::Collider>(*this);
        AddComponent<Component::Health>(*this);
	}

    void Phoenix::Update()
    {
        // If Health <= 0, Set texture to Flag and set gameOver
    }

    void Phoenix::ResolveCollisions(Object&)
    {
        // Empty
    }

    void Phoenix::OnOutOfBounds(const Vector2Int&)
    {
        // Empty
    }
}
