#pragma once

#include "Object.h"

namespace BattleCity::Object
{
    class Wall final : public Object
    {
    public:
        Wall(int x, int y);
        ~Wall() override = default;

        void Update() override;
    };
}

