#pragma once

#include "Event.h"
#include "Object.h"

namespace BattleCity
{
	class PowerUp final : public Object
	{
    public:
        PowerUp();

        void Update(const float& deltaTime) override;

        void EventHandler(Event& event) override;
	};
}

