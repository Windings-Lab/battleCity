#pragma once

#include "Component.h"
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

		void SetBulletCount(int count) noexcept;
		int GetBulletCount() const noexcept;

		Position GetShootPosition(Direction);

	private:
		std::function<std::shared_ptr<Bullet>(Position, Direction)> mSpawnBullet;

		int mBulletCount = 0;
	};
}


