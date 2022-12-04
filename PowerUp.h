#pragma once

#include "Event.h"
#include "Object.h"

namespace battleCity
{
	class PowerUp final : public Object
	{
    public:
        PowerUp();

        void Update() override;

        void EventHandler(Event& event) override;
	};
}

