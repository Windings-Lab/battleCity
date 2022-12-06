#pragma once

#include "Event.h"
#include "Object.h"

namespace BattleCity
{
    class Explosion final : public Object
    {
    public:
	    explicit Explosion(bool isLarge);

        void Update(float) override;

        void EventHandler(Event& eventPtr) override;

    private:
        void HandleAnimation();
    };
}