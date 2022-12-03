#pragma once
#include "Object.h"

namespace battleCity
{
    class Wall : public Object
    {
    public:
        Wall();
        ~Wall();
        Wall(float x, float y);

        void Update() override;
        void Draw() override;
    };
}

