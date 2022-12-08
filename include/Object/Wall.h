#pragma once

#include "Object.h"

namespace BattleCity::Object
{
    class Wall final : public Object
    {
    public:
        Wall();
        ~Wall() override = default;

        void Update() override;

        void EventHandler(Event& ptrEvent) override;
    };
}

