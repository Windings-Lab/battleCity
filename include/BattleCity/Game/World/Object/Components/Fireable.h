#pragma once

#include "Component.h"
#include "BattleCity/Engine/Timer.h"
#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

namespace BattleCity::Game::World::Object
{
	namespace Factory
	{
		struct Standart;
	}

	class Bullet;
	class Object;
}

namespace BattleCity::Game::World::Object::Component
{
	class Collider;

	class Fireable : public Component
	{
	public:
		explicit Fireable(Object&);

		ALLOW_COPY_MOVE_DEFAULT(Fireable)

		~Fireable() override = default;

		virtual void Fire();

		void SetBullet(Factory::Standart&);
		void SetBulletCount(int) noexcept;

	private:
		Position GetShootPosition(Direction);

	private:
		Collider* mCollider;

		std::function<std::shared_ptr<Bullet>(Position, Direction, Type)> mSpawnBullet;
		std::vector<std::weak_ptr<Bullet>> mBullets;

		int mMaxBulletCount;
	};
}


