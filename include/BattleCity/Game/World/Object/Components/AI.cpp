#include "PCHeader.h"
#include "AI.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "Movable.h"
#include "Fireable.h"

namespace BattleCity::Game::World::Object::Component
{
	AI::AI(Object& obj)
		: Component(obj)
		, mMovable(mObject.GetComponent<Movable>())
		, mFireable(mObject.GetComponent<Fireable>())
		, mRandomGenerator(std::random_device{}())
		, mRandomDirection(0,3)
	{
		mTimeToChangeDirection.StartRandom(3, 10, [this]
			{
				RandomChangeDirection();
			});

		mTimeToShoot.StartRandom(0, 3, [this]
			{
				mFireable->Fire();
			});
	}

	void AI::Update()
	{
		mTimeToChangeDirection.RepeatRandom(3, 10);
		mTimeToShoot.RepeatRandom(0, 3);
	}

	void AI::RandomChangeDirection()
	{
		mMovable->SetMovementDirection(static_cast<Direction>(mRandomDirection(mRandomGenerator)));
	}
}

