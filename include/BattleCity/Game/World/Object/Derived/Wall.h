#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Collider;
		class Health;
	}

	class Wall : public Object
    {
    public:
	    explicit Wall(const Position&, const std::function<void(ID, Layer)>&);

        void Update() override;
        void ResolveCollisions(Object&) override;
        void OnOutOfBounds(const Vector2Int&) override;

	private:
        Component::Health* mHealth;
        Component::Collider* mCollider;
    };
}

