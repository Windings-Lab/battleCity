#pragma once
#include "Object.h"
#include "Event.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "Screen.h"

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

        void makePowerUp(const battleCity::EventCollision* collisionEvent);

        int eventHandler(const Event* ptrEvent);
	};
}

