#pragma once

#include "Object.h"

namespace BattleCity::Object
{
    class Explosion final : public Object
    {
    public:
	    explicit Explosion(bool isLarge);

        void Update() override;
    };
}