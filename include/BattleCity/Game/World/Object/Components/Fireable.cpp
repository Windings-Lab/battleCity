#include "PCHeader.h"
#include "Fireable.h"

#include "BattleCity/Game/World/Object/Derived/Bullet.h"

namespace BattleCity::Game::World::Object::Component
{
	Fireable::Fireable(std::function<std::shared_ptr<Bullet>()> fire)
		: mSpawnBullet(std::move(fire))
		, mBulletCount(0)
	{

	}

	void Fireable::Fire(const Position& position, const Direction& direction)
	{
		if(mBulletCount > 0)
		{
			auto bullet = mSpawnBullet();
			bullet->SetPosition(position);
			bullet->SetDirection(direction);
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
