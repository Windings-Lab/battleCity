#pragma once
#include "Object.h"

namespace battleCity
{
    class Wall final : public Object
    {
    public:
        Wall();

        void Update() override;
    };
}

