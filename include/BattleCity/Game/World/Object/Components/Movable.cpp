#include "PCHeader.h"
#include "Movable.h"

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	Vector2Int Movable::GetSpeed() const noexcept
	{
		return mDirection * mSpeed;
	}

	Movable& Movable::SetSpeed(Speed speed) noexcept
	{
		mSpeed = speed;
		return *this;
	}

	Movable& Movable::SetDirection(MovementDirection direction) noexcept
	{
		switch (direction)
		{
			case MovementDirection::Left:
				mDirection = { -1, 0 };
				break;
			case MovementDirection::Right:
				mDirection = { 1, 0 };
				break;
			case MovementDirection::Up:
				mDirection = { 0, -1 };
				break;
			case MovementDirection::Down:
				mDirection = { 0, 1 };
				break;
			case MovementDirection::Count:
			default: break;
		}

		return *this;
	}
	const Direction& Movable::GetDirection() const noexcept
	{
		return mDirection;
	}

	void Movable::StopMovement() noexcept
	{
		mDirection = { 0, 0 };
	}
}
