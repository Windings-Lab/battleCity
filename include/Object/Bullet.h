#pragma once

#include "Event.h"
#include "EventCollision.h"
#include "Object.h"

namespace BattleCity
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

        void Update(const float& deltaTime) override;

        void EventHandler(Event& myEvent) override;
    private:
        void OutOfWorld();
        void Hit(EventCollision collisionEvent);

        Type mOwnerType;
    };
}
