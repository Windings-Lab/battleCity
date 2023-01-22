#include "PCHeader.h"
#include "Movable.h"

#include "TextureComponent.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	const Velocity& Movable::GetVelocity() const noexcept
	{
		return mVelocity;
	}

	void Movable::SetSpeed(Speed speed) noexcept
	{
		mSpeed = speed;
	}

	void Movable::SetMovementDirection(Direction direction) noexcept
	{
		auto textureComponent = mObject.GetComponent<Texture>();

		switch (direction)
		{
			case Direction::Left:
				mVelocity.X = -mSpeed;
				mVelocity.Y = 0;
				textureComponent->ChangeTextureTo(Framework::TextureType::Left);
				break;
			case Direction::Right:
				mVelocity.X = mSpeed;
				mVelocity.Y = 0;
				textureComponent->ChangeTextureTo(Framework::TextureType::Right);
				break;
			case Direction::Up:
				mVelocity.X = 0;
				mVelocity.Y = -mSpeed;
				textureComponent->ChangeTextureTo(Framework::TextureType::Up);
				break;
			case Direction::Down:
				mVelocity.X = 0;
				mVelocity.Y = mSpeed;
				textureComponent->ChangeTextureTo(Framework::TextureType::Down);
				break;
			case Direction::Count:
			default:
				{
					assert(false && "Movable: Invalid SetMovementDirection");
				}
				break;
		}

		mMoving = true;
		mMovementDirection = direction;
	}
	Direction Movable::GetMovementDirection() const noexcept
	{
		return mMovementDirection;
	}

	void Movable::StopMovement() noexcept
	{
		mVelocity.X = 0;
		mVelocity.Y = 0;
		mMoving = false;
	}
	bool Movable::IsMoving() const noexcept
	{
		return mMoving;
	}
}
