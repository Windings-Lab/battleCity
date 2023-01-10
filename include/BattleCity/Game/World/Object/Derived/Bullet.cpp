#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::Update()
    {
    }

    void Bullet::SetPosition(Position pos) noexcept
    {
	    const Size bulletSize = GetSize();
        
        pos.X -= bulletSize.X / 2;
        pos.Y -= bulletSize.Y;

        Object::SetPosition(pos);
    }
}
