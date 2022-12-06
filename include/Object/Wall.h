#pragma once

#include "Object.h"

namespace BattleCity
{
    class Wall final : public Object
    {
    public:
        Wall();
        ~Wall() override = default;

        void Update(const float& deltaTime) override;

        void EventHandler(Event& ptrEvent) override;
    };
}

