#include "PCHeader.h"
#include "Movable.h"

namespace BattleCity::Game::World::Object::Component
{
	Movable::Movable() : mSpeed(0)
	{
	}

	Vector2Int Movable::GetSpeedDirection() const noexcept
	{
		return mDirection * mSpeed;
	}

	void Movable::SetSpeed(Speed speed) noexcept
	{
		mSpeed = speed;
	}

	void Movable::SetDirection(Direction direction) noexcept
	{
		mDirection = direction;
	}
	const Direction& Movable::GetDirection() const noexcept
	{
		return mDirection;
	}
}
