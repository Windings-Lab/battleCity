#pragma once

#include "Object.h"

namespace battleCity
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

