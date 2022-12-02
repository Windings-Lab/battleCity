#pragma once
#include "Object.h"
#include "EventCollision.h"

namespace battleCity
{
    class Bullet : public Object
    {
    private:
        void out();
        void hit(EventCollision collisionEvent);

        Object& mObjectOwner;
    public:
        Bullet(int objID);
        ~Bullet();

        void initBullet();

        void draw() override;

        int EventHandler(Event event) override;
    };
}
