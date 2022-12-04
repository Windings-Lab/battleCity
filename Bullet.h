#pragma once
#include "Event.h"
#include "EventCollision.h"
#include "Object.h"

namespace battleCity
{
    class Bullet final : public Object
    {
    public:
	    explicit Bullet(Type ownerType);

        Bullet(const Bullet&) = delete;
        Bullet(Bullet&&) = delete;

        Bullet& operator=(const Bullet&) = delete;
        Bullet& operator=(Bullet&&) = delete;

        ~Bullet() override;

        void Update() override;

        void EventHandler(Event& event) override;
    private:
        void OutOfWorld();
        void Hit(EventCollision collisionEvent);

        Type mOwnerType;
    };
}
