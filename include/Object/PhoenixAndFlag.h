#pragma once

#include "Event.h"
#include "EventCollision.h"
#include "Object.h"

namespace BattleCity::Object
{
	class PhoenixAndFlag final : public Object
	{
    public:
        PhoenixAndFlag(float x, float y);

        void Update() override;

        void EventHandler(Event& event) override;
	private:
        void OnHit(EventCollision& collisionEvent);
	};
}

