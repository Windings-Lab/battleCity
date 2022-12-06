#pragma once

#include "Event.h"
#include "EventCollision.h"
#include "Object.h"

namespace BattleCity
{
	class PhoenixAndFlag final : public Object
	{
    public:
        PhoenixAndFlag(float x, float y);

        void Update(float) override;

        void EventHandler(Event& event) override;
	private:
        void OnHit(EventCollision& collisionEvent);
	};
}

