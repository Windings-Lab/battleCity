#pragma once
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Pixel : public Object
	{
	public:
		Pixel();

		void Update() override;
		void ResolveCollisions(Object&) override;
	};
}


