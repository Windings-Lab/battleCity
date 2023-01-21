#include "PCHeader.h"
#include "Movable.h"

#include "TextureComponent.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	Vector2Int Movable::GetSpeed() const noexcept
	{
		return mVelocity * mSpeed;
	}

	void Movable::SetSpeed(Speed speed) noexcept
	{
		mSpeed = speed;
	}

	void Movable::SetDirection(Direction direction) noexcept
	{
		auto textureComponent = mObject.GetComponent<Texture>();

		switch (direction)
		{
			case Direction::Left:
				mVelocity = { -1, 0 };
				textureComponent->ChangeTextureTo(Framework::TextureType::Left);
				break;
			case Direction::Right:
				mVelocity = { 1, 0 };
				textureComponent->ChangeTextureTo(Framework::TextureType::Right);
				break;
			case Direction::Up:
				mVelocity = { 0, -1 };
				textureComponent->ChangeTextureTo(Framework::TextureType::Up);
				break;
			case Direction::Down:
				mVelocity = { 0, 1 };
				textureComponent->ChangeTextureTo(Framework::TextureType::Down);
				break;
			case Direction::Count:
			default:
				{
					assert(false && "Movable: Invalid SetDirection");
				}
				break;
		}

		mDirection = direction;
	}
	Direction Movable::GetDirection() const noexcept
	{
		return mDirection;
	}

	void Movable::StopMovement() noexcept
	{
		mVelocity = { 0, 0 };
	}
}
