#pragma once

#include "Object.h"

namespace BattleCity::Event
{
    class EventCollision;
}

namespace BattleCity::Object
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

        void EventHandler(Event::Event& myEvent) override;
    private:
        void OutOfWorld();
        void Hit(Event::EventCollision& collisionEvent);

        Type mOwnerType;
    };
}
