#pragma once
#include "Object.h"

namespace battleCity
{
    class Wall : public Object
    {

    public:
        Wall();

        void update() override;
        void draw() override;

        int eventHandler(const Event* ptrEvent);
    };
}

