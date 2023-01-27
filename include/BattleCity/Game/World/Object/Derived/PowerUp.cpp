#include "PCHeader.h"

#include "PowerUp.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	PowerUp::PowerUp() : Object()
	{
		AddComponent<Component::Texture>();
		AddComponent<Component::Collider>();
	}
}
