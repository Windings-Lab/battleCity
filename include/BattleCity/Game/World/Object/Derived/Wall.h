#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Health;
	}

	class Wall : public Object
    {
    public:
        Wall();

        void Update() override;
        void ResolveCollisions(Object&) override;

	private:
        Component::Health* mHealth;
    };
}

