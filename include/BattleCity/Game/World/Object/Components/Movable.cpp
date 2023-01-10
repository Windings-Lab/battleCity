#include "PCHeader.h"
#include "Movable.h"

namespace BattleCity::Game::World::Object::Component
{
	Movable::Movable() : mSpeed(0)
	{
	}

	Vector2Int Movable::GetSpeed() const noexcept
	{
		return mDirection * mSpeed;
	}

	Movable& Movable::SetSpeed(Speed speed) noexcept
	{
		mSpeed = speed;
		return *this;
	}

	Movable& Movable::SetDirection(Direction direction) noexcept
	{
		mDirection = direction;
		return *this;
	}
	const Direction& Movable::GetDirection() const noexcept
	{
		return mDirection;
	}
}
