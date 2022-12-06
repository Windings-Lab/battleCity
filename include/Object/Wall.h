#pragma once

#include "Object.h"

namespace BattleCity
{
    class Wall final : public Object
    {
    public:
        Wall();
        ~Wall() override = default;

        void Update(float) override;

        void EventHandler(Event& ptrEvent) override;
    };
}

