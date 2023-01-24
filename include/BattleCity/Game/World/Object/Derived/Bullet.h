#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Explodable;
		class Collider;
		class Movable;
		class Texture;
	}

	class Bullet : public Object
    {
    public:
        Bullet();

        void Update() override;
        void ResolveCollisions(Object&) override;
        void OnOutOfBounds(const Vector2Int&) override;
        void OnDestroy() override;

        void SetIgnoreColliderType(Type) noexcept;

        void AdjustPositionToDirection();

	private:
        Component::Texture* mTexture;
        Component::Movable* mMovable;
        Component::Collider* mCollider;
        Component::Explodable* mExplodable;

        Type mIgnoreColliderType;
    };
}
