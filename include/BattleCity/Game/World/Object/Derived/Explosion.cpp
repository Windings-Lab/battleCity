#include "PCHeader.h"

#include "Explosion.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Explosion::Explosion() : Object()
	{
        AddComponent<Component::Texture>(*this);
	}

    void Explosion::Update()
    {
        // Update animation
    }
    void Explosion::ResolveCollisions(Object&)
    {
        // Empty
    }
    void Explosion::OnOutOfBounds(const Vector2Int&)
    {
        // Empty
    }
}
