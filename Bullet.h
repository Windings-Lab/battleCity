#pragma once
#include "Object.h"
#include "EventCollision.h"

namespace battleCity
{
    class Bullet : public Object
    {
    private:
        void out();
        void hit(const EventCollision* collisionEvent);

        Object& mObjectOwner;
    public:
        Bullet(int objOwnerID);
        ~Bullet();

        void initBullet();

        void draw() override;

        int eventHandler(const Event* ptrEvent);
    };
}
