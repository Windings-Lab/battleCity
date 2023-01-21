#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
    class Explosion : public Object
    {
    public:
        Explosion();

        void Update() override;
        void ResolveCollisions(Object&) override;
    };
}
