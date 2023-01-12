#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Collider;
		class Movable;
		class Fireable;
	}

	class Tank : public Object
	{
	public:
		using Object::Object;

		void OnComponentInitialization() override;

		void Update() override;

		void Fire();

	private:
		Component::Fireable* mFireable;
		Component::Movable* mMovable;
		Component::Collider* mCollider;
	};
}
