#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Phoenix : public Object
	{
    public:
		Phoenix();

		void Update() override;
		void ResolveCollisions(const Object&) override;
	};
}

