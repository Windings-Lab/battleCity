#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Health;
		class Explodable;
		class Fireable;
		class Movable;
		class Collider;
		class Texture;
	}

	class Tank : public Object
	{
	public:
		explicit Tank(const Position&, const std::function<void(ID, Layer)>&);

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;

		void OnDestroy() override;

	protected:
		Component::Texture* mTexture;
		Component::Collider* mCollider;
		Component::Movable* mMovable;
		Component::Fireable* mFireable;
		Component::Explodable* mExplodable;
		Component::Health* mHealth;
	};
}
