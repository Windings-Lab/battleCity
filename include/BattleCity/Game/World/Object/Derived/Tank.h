#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Movable;
		class Fireable;
	}

	class Tank : public Object
	{
	public:
		using Object::Object;

		void Fire();

	private:
		void OnComponentAdd() override;
		Position GetBulletSpawnPosition() const noexcept;

	private:
		Component::Fireable* mFireable;
		Component::Movable* mMovable;

	};
}
