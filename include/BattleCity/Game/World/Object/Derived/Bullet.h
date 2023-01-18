#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Movable;
	}

	class Bullet : public Object
    {
    public:
        using Object::Object;

        void Update() override;

        void SetDirection(MovementDirection) noexcept;

	private:
        void InitializeComponents() override;

    private:
        Component::Movable* mMovable;
    };
}
