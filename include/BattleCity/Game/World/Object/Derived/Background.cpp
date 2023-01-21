#include "PCHeader.h"
#include "Background.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Background::Background()
	{
        AddComponent<Component::Texture>(*this);
	}

    void Background::Update()
    {
        // Empty
    }
    void Background::ResolveCollisions(const Object&)
    {
        // Empty
    }
}

