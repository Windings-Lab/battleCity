#pragma once

#include "Object.h"

namespace BattleCity::Object
{
    class Bullet final : public Object
    {
    public:
	    explicit Bullet(Type ownerType);

    private:
        Type mOwnerType;
    };
}
