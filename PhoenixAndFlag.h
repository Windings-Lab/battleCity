#pragma once
#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

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

        void Draw() override;

        void setGameOver(EventCollision& collisionEvent);

        int EventHandler(Event& event) override;
	};
}

