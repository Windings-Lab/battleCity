#pragma once
#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

namespace battleCity
{
	class PhoenixAndFlag final : public Object
	{
    public:
        PhoenixAndFlag(float x, float y);

        void Update() override;
        void Draw() override;

        void EventHandler(Event& event) override;
	private:
        void OnHit(EventCollision& collisionEvent);
	};
}

