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

        Object& object;
        /*int objectID;*/
        std::string objectType;
    public:
        Bullet(Object& ptrObj);
        ~Bullet();

        void initBullet(const Object& ptrObj);

        void update() override;
        void draw() override;

        int eventHandler(const battleCity::Event* ptrEvent);
    };
}
