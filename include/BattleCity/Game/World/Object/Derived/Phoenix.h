#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Collider;
	}

	class Phoenix : public Object
	{
    public:
		using Object::Object;

		void OnComponentInitialization() override;
		void Update() override;

	private:
		Component::Collider* mCollider;
	};
}

