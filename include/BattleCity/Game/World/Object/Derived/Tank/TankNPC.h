#pragma once

#include "BattleCity/Game/World/Object/Derived/Tank.h"

namespace BattleCity::Game::World::Object
{
	class TankNPC : public Tank
	{
	public:
		using Tank::Tank;

		void ResolveCollisions(Object&) override;
	};
}


