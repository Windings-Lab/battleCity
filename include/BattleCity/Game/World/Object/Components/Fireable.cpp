#include "PCHeader.h"
#include "Fireable.h"

#include "Movable.h"
#include "TextureComponent.h"
#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Game::World::Object::Component
{
	void Fireable::Fire()
	{
		if(mBulletCount <= 0) return;

		auto shootDirection = mObject.GetComponent<Movable>()->GetDirection();
		auto bullet = mSpawnBullet(GetShootPosition(shootDirection), shootDirection);
	}
	void Fireable::SetBullet(Factory::Standart& objectFactory)
	{
		mSpawnBullet = [&objectFactory](Position position, Direction direction) { return objectFactory.CreateBullet(position, direction); };
	}
	void Fireable::SetBulletCount(int count) noexcept
	{
		mBulletCount = count;
	}
	int Fireable::GetBulletCount() const noexcept
	{
		return mBulletCount;
	}

	Position Fireable::GetShootPosition(Direction direction)
	{
		auto& objectSize = mObject.GetComponent<Texture>()->GetSize();
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
