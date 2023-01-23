#include "PCHeader.h"
#include "AI.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "Movable.h"
#include "Fireable.h"
#include "Health.h"

namespace BattleCity::Game::World::Object::Component
{
	AI::AI(Object& obj)
		: Component(obj)
		, mMovable(mObject.GetComponent<Movable>())
		, mFireable(mObject.GetComponent<Fireable>())
		, mHealth(mObject.GetComponent<Health>())
		, mRandomGenerator(std::random_device{}())
		, mRandomDirection(0,3)
	{
		mTimeToChangeDirection.StartRandom(3, 5, [this]
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
		if(mHealth && mHealth->GetHealth() <= 0) return;

		mTimeToChangeDirection.RepeatRandom(3, 5);
		mTimeToShoot.RepeatRandom(0, 3);
		mOnWallCollision.Update();
	}

	void AI::RandomChangeDirection()
	{
		mMovable->SetMovementDirection(static_cast<Direction>(mRandomDirection(mRandomGenerator)));
	}

	void AI::OnWallCollision()
	{
		mOnWallCollision.StartOnceRandom(0, 2, [this]
		{
			RandomChangeDirection();
		});
	}
}

