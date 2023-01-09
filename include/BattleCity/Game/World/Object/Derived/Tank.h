#pragma once

#include "BattleCity/Game/World/Object/Object.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
	class Tank : public Object
	{
	public:
		using Object::Object;

	private:
		Position GetBulletSpawnPosition() const noexcept;
	};
}
