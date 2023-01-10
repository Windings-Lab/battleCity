#pragma once

#include "Component.h"
#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object
{
	class Bullet;
	class Object;
}

namespace BattleCity::Game::World::Object::Component
{
	class Fireable : public Component
	{
	public:
		Fireable(std::function<std::shared_ptr<Bullet>()>);

		ALLOW_COPY_MOVE_DEFAULT(Fireable)

		~Fireable() override = default;

		virtual void Fire(const Position&, const Direction&);

		void SetBulletCount(int count) noexcept;
		int GetBulletCount() const noexcept;

	private:
		std::function<std::shared_ptr<Bullet>()> mSpawnBullet;

		int mBulletCount;
	};
}


