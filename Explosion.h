#pragma once
#include "Object.h"
#include "Event.h"

namespace battleCity
{
    class Explosion : public Object
    {
    private:
        void step();
        int spriteIndex;
    public:
        Explosion(bool isLarge);

        void Draw() override;

        int EventHandler(Event& eventPtr) override;
    };
}