#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Wall : public Object
    {
    public:
        Wall();

        void Update() override;
        void ResolveCollisions(Object&) override;
    };
}

