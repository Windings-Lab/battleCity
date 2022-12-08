#pragma once

#include "Object.h"

namespace BattleCity::Object
{
    class Bullet final : public Object
    {
    public:
	    explicit Bullet(Type ownerType);

        Bullet(const Bullet&) = delete;
        Bullet(Bullet&&) = delete;

        Bullet& operator=(const Bullet&) = delete;
        Bullet& operator=(Bullet&&) = delete;

        ~Bullet() override;

        void Update() override;
    private:
        Type mOwnerType;
    };
}
