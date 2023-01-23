#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Fireable;
		class Movable;
		class Collider;
		class Texture;
	}

	class Tank : public Object
	{
	public:
		Tank();

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;

	protected:
		Component::Texture* mTexture;
		Component::Collider* mCollider;
		Component::Movable* mMovable;
		Component::Fireable* mFireable;
	};
}
