#include "PCHeader.h"

#include "PowerUp.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	PowerUp::PowerUp(const Position& pos, const std::function<void(ID, Layer)>& d) : Object(pos, d)
	{
		AddComponent<Component::Texture>();
		AddComponent<Component::Collider>();
	}
}
