#pragma once

#include "Object.h"

namespace BattleCity::Object
{
	class PhoenixAndFlag final : public Object
	{
    public:
        PhoenixAndFlag(float x, float y);

        void Update() override;
	};
}

