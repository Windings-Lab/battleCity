#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
    class Bullet : public Object
    {
    public:
        using Object::Object;

        void Update() override;

        void SetPosition(Position) noexcept override;
    };
}
