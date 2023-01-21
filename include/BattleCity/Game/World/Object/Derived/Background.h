#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Background final : public Object
	{
	public:
		Background();

		void Update() override;
		void ResolveCollisions(const Object&) override;
	};
}
