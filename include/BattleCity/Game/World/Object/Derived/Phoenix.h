#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Collider;
		class Explodable;
		class Texture;
		class Health;
	}

	class Phoenix : public Object
	{
    public:
		explicit Phoenix(const Position&, const std::function<void(ID, Layer)>&);

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;

	private:
		Component::Collider* mCollider;
		Component::Health* mHealth;
		Component::Texture* mTexture;
		Component::Explodable* mExplodable;
	};
}

