#include "PCHeader.h"
#include "Fireable.h"

#include "Collider.h"
#include "Movable.h"
#include "TextureComponent.h"
#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Game::World::Object::Component
{
	Fireable::Fireable(Object& obj)
		: Component(obj)
		, mCollider(mObject.GetComponent<Collider>())
	{
	}

	void Fireable::Fire()
	{
		mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(),
			[](const auto& weak)
			{
				return weak.expired();
			}), mBullets.end());
		if(mBullets.size() >= mMaxBulletCount) return;

		auto shootDirection = mObject.GetComponent<Movable>()->GetMovementDirection();
		mBullets.emplace_back(mSpawnBullet(GetShootPosition(shootDirection), shootDirection, mCollider->GetColliderType()));
	}
	void Fireable::SetBullet(Factory::Standart& objectFactory)
	{
		mSpawnBullet = [&objectFactory](Position position, Direction direction, Type type) { return objectFactory.CreateBullet(position, direction, type); };
	}

	void Fireable::SetBulletCount(int count) noexcept
	{
		mMaxBulletCount = count;
	}

	Position Fireable::GetShootPosition(Direction direction)
	{
		auto& objectSize = mCollider->GetSize();
		const auto objectHalfSize = objectSize / 2;
		auto shootPosition = mObject.GetPosition();

		switch (direction)
		{
		case Direction::Right:
			shootPosition.X += objectSize.X;
		case Direction::Left:
			shootPosition.Y += objectHalfSize.Y;
			break;

		case Direction::Down:
			shootPosition.Y += objectSize.Y;
		case Direction::Up:
			shootPosition.X += objectHalfSize.X;
			break;

		case Direction::Count:
		default:
			assert(false && "Invalid Tank direction");
			return {};
		}

		return shootPosition;
	}
}
