#pragma once

#include "Component.h"
#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

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
		using Component::Component;

		ALLOW_COPY_MOVE_DEFAULT(Fireable)

		~Fireable() override = default;

		virtual void Fire();

		void SetBullet(const std::function<std::shared_ptr<Bullet>(Position)>&);

		void SetBulletCount(int count) noexcept;
		int GetBulletCount() const noexcept;

	private:
		std::function<std::shared_ptr<Bullet>(Position)> mSpawnBullet;

		int mBulletCount = 0;
	};
}


