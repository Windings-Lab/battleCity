#pragma once
#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

namespace battleCity
{
	class PowerUp : public Object
	{
    private:
        int indexX;
        int indexY;
    public:
        PowerUp();
        ~PowerUp();
        PowerUp(int giveHealth);

        void draw() override;

        void makePowerUp(EventCollision& collisionEvent);

        int EventHandler(Event& event) override;
	};
}

