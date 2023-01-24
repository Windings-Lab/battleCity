#pragma once
#include "Component.h"

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object::Factory
{
	struct Standart;
}

namespace BattleCity::Game::World::Object::Component
{
	class Collider;

	class Explodable : public Component
	{
	public:
		explicit Explodable(Object&);

		void SetExplosionSpawner(Factory::Standart&);

		void SetExplodable(bool) noexcept;
		void Explode(ExplosionType);

	private:
		std::function<void(ExplosionType, Position)> mSpawnExplosion;
		bool mExplodable;

		const Collider* mCollider;
	};
}


