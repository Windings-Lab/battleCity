#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object
{
	class Bullet;
	class Object;
}

namespace BattleCity::Game::World::Object::Component
{
	class Fireable
	{
	public:
		Fireable(std::function<std::shared_ptr<Object>()>);

		ALLOW_COPY_MOVE_DEFAULT(Fireable)

		virtual ~Fireable() = default;

		virtual void Fire(const Position&);

		void SetBulletCount(int count) noexcept;
		int GetBulletCount() const noexcept;

	private:
		std::function<std::shared_ptr<Object>()> mSpawnBullet;

		int mBulletCount;
	};
}


