#include "PCHeader.h"
#include "Fireable.h"

#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object::Component
{
	Fireable::Fireable(std::function<std::shared_ptr<Bullet>()> fire)
		: mSpawnBullet(std::move(fire))
		, mBulletCount(0)
	{

	}

	void Fireable::Fire(Position position, const Direction& direction)
	{
		if(mBulletCount > 0)
		{
			auto bullet = mSpawnBullet();

			const Size bulletSize = bullet->GetSize();

			position.X -= bulletSize.X / 2;
			position.Y -= bulletSize.Y;

			bullet->SetPosition(position);
			bullet->GetComponent<Movable>()->SetDirection(direction);
		}
	}
	void Fireable::SetBulletCount(int count) noexcept
	{
		mBulletCount = count;
	}
	int Fireable::GetBulletCount() const noexcept
	{
		return mBulletCount;
	}
}
