#pragma once

#include "Object.h"

namespace BattleCity::Event
{
    class EventCollision;
}

namespace BattleCity::Object
{
	class PhoenixAndFlag final : public Object
	{
    public:
        PhoenixAndFlag(float x, float y);

        void Update() override;

        void EventHandler(Event::Event& event) override;
	private:
        void OnHit(Event::EventCollision& collisionEvent);
	};
}

