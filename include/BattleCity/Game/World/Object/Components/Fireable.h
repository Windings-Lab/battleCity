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
	class Fireable : public Component
	{
	public:
		using Component::Component;

		ALLOW_COPY_MOVE_DEFAULT(Fireable)

		~Fireable() override = default;

		virtual void Fire();

		void SetBullet(Factory::Standart&);
		void SetBulletCount(int) noexcept;

	private:
		Position GetShootPosition(Direction);
		void EraseDestroyedBullets();

	private:
		std::function<std::shared_ptr<Bullet>(Position, Direction)> mSpawnBullet;
		std::vector<std::weak_ptr<Bullet>> mBullets;

		int mMaxBulletCount;
	};
}


