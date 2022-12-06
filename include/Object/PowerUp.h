#pragma once

#include "Event.h"
#include "Object.h"

namespace BattleCity
{
	class PowerUp final : public Object
	{
    public:
        PowerUp();

        void Update(float) override;

        void EventHandler(Event& event) override;
	};
}

