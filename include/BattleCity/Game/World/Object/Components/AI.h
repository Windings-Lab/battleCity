#pragma once
#include "BattleCity/Engine/Timer.h"
#include "BattleCity/Game/World/Object/Components/Component.h"

namespace BattleCity::Game::World::Object::Component
{
	class Fireable;
	class Movable;

	class AI : public Component
	{
	public:
		explicit AI(Object&);

		void Update();

		void RandomChangeDirection();

	private:
		Movable* mMovable;
		Fireable* mFireable;

		Engine::Timer mTimeToChangeDirection;
		Engine::Timer mTimeToShoot;

		std::mt19937 mRandomGenerator;
		std::uniform_int_distribution<int> mRandomDirection;
	};
}


