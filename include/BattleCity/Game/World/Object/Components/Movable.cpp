#include "PCHeader.h"
#include "Movable.h"

#include "BattleCity/Framework/Texture.h"
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

	Movable& Movable::SetDirection(Framework::TextureType direction) noexcept
	{
		switch (direction)
		{
			case Framework::TextureType::Left:
				mDirection = { -1, 0 };
				break;
			case Framework::TextureType::Right:
				mDirection = { 1, 0 };
				break;
			case Framework::TextureType::Up:
				mDirection = { 0, -1 };
				break;
			case Framework::TextureType::Down:
				mDirection = { 0, 1 };
				break;
			default: ;
		}

		mObject.ChangeTextureTo(direction);

		return *this;
	}
	Movable& Movable::ResetDirection() noexcept
	{
		mDirection = { 0, 0 };
		return *this;
	}
	const Direction& Movable::GetDirection() const noexcept
	{
		return mDirection;
	}
}
