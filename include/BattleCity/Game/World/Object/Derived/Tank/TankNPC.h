#pragma once

#include "BattleCity/Game/World/Object/Derived/Tank.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class AI;
	}

	class TankNPC : public Tank
	{
	public:
		TankNPC();

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;

	private:
		Component::AI* mAi;
	};
}


