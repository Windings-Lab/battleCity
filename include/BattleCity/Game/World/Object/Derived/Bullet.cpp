#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::Update()
    {
    }

    void Bullet::SetPosition(Position pos) noexcept
    {
        int bulletWidth, bulletHeight;

        GetTextureSize(bulletWidth, bulletHeight);
        
        pos.X -= bulletWidth / 2;
        pos.Y -= bulletHeight;

        Object::SetPosition(pos);
    }
}
