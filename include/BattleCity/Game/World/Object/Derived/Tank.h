#pragma once

#include "BattleCity/Game/World/Object/Object.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"

namespace BattleCity::Game::World::Object
{
	class Tank : public Object
	{
	public:
		Tank(const Engine::Texture::Group&, std::function<std::shared_ptr<Object>()>);

		void Fire();

		void SetBulletCount(int) noexcept;

	private:
		Position GetBulletSpawnPositon() const noexcept;

	private:
		Component::Fireable mFireable;
	};
}
