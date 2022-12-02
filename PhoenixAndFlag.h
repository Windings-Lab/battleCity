#pragma once
#include "Object.h"
#include "Event.h"
#include "EventCollision.h"
#include "Vector.h"

namespace battleCity
{
	class PhoenixAndFlag : public Object
	{
    private:
        bool gameOver;
    public:
        /*PhoenixAndFlag();*/
        PhoenixAndFlag(float x, float y);
        ~PhoenixAndFlag();

        void draw() override;

        void setGameOver(const battleCity::EventCollision* collisionEvent);

        int eventHandler(const Event* ptrEvent);
	};
}

