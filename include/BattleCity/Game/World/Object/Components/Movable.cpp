#include "PCHeader.h"
#include "Movable.h"

#include "TextureComponent.h"
#include "Collider.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object::Component
{
	Movable::Movable(Object& obj)
		: Component(obj)
		, mCollider(mObject.GetComponent<Collider>())
		, mTexture(mObject.GetComponent<Texture>())
		, mMoving(false)
		, mMovementDirection(Direction::Error)
	{
	}

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
		switch (direction)
		{
			case Direction::Left:
				mVelocity.X = -mSpeed;
				mVelocity.Y = 0;
				if(mTexture) mTexture->ChangeTextureTo(Framework::TextureType::Left);
				break;
			case Direction::Right:
				mVelocity.X = mSpeed;
				mVelocity.Y = 0;
				if (mTexture) mTexture->ChangeTextureTo(Framework::TextureType::Right);
				break;
			case Direction::Up:
				mVelocity.X = 0;
				mVelocity.Y = -mSpeed;
				if (mTexture) mTexture->ChangeTextureTo(Framework::TextureType::Up);
				break;
			case Direction::Down:
				mVelocity.X = 0;
				mVelocity.Y = mSpeed;
				if (mTexture) mTexture->ChangeTextureTo(Framework::TextureType::Down);
				break;
			case Direction::Count:
			default:
				{
					assert(false && "Movable: Invalid SetMovementDirection");
				}
				break;
		}

		if (mCollider && mTexture) mCollider->SetSize(mTexture->GetSize());

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
