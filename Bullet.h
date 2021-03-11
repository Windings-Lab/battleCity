#pragma once
#include "Object.h"
#include "EventCollision.h"
#include "Sprites.h"

namespace battleCity
{
    class Bullet : public Object
    {
    private:
        void out();
        void hit(const battleCity::EventCollision* CollisionEvent);
    public:
        void update() override;
        void draw() override;

        Bullet(battleCity::Object* ptrObj);
        int eventHandler(const battleCity::Event* ptrEvent);
    };
}
