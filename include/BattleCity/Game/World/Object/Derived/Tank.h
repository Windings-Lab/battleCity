#pragma once

#include "BattleCity/Game/World/Object/Object.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
	class Tank : public Object
	{
	public:
		Tank(const Engine::Texture::Group&, std::function<std::shared_ptr<Bullet>()>);

		void SetSpeed(Speed) noexcept;
		void SetDirection(Direction) noexcept;

		void Fire();
		void SetBulletCount(int) noexcept;

	private:
		Position GetBulletSpawnPositon() const noexcept;

	private:
		Component::Movable mMovable;
		Component::Fireable mFireable;
	};
}
