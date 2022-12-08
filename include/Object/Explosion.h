#pragma once

#include "Event.h"
#include "Object.h"

namespace BattleCity::Object
{
    class Explosion final : public Object
    {
    public:
	    explicit Explosion(bool isLarge);

        void Update() override;

        void EventHandler(Event::Event& eventPtr) override;
    };
}