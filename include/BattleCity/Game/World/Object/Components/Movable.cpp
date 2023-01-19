#include "PCHeader.h"
#include "Movable.h"

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	Vector2Int Movable::GetSpeed() const noexcept
	{
		return mVelocity * mSpeed;
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
				mVelocity = { -1, 0 };
				break;
			case MovementDirection::Right:
				mVelocity = { 1, 0 };
				break;
			case MovementDirection::Up:
				mVelocity = { 0, -1 };
				break;
			case MovementDirection::Down:
				mVelocity = { 0, 1 };
				break;
			case MovementDirection::Count:
			default:
				{
					assert(false && "Movable: Invalid SetDirection");
				}
				break;
		}

		mDirection = direction;

		return *this;
	}
	MovementDirection Movable::GetDirection() const noexcept
	{
		return mDirection;
	}

	void Movable::StopMovement() noexcept
	{
		mVelocity = { 0, 0 };
	}
}
