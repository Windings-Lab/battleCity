#include "PCHeader.h"
#include "Background.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Background::Background(const Position& pos, const std::function<void(ID, Layer)>& d) : Object(pos, d)
	{
        AddComponent<Component::Texture>();
	}

    void Background::Update()
    {
        // Empty
    }
    void Background::ResolveCollisions(Object&)
    {
        // Empty
    }
    void Background::OnOutOfBounds(const Vector2Int&)
    {
        // Empty
    }
}

