#pragma once

#include "Object.h"

namespace BattleCity::Object
{
	class PowerUp final : public Object
	{
    public:
        PowerUp();

        void Update() override;
	};
}

