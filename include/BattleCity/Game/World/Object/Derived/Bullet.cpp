#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::Update()
    {
    }

    void Bullet::SetPosition(const Position& pos) noexcept
    {
        int bulletWidth, bulletHeight;

        GetTextureSize(bulletWidth, bulletHeight);

        Position bulletPosition(pos.X, pos.Y);

        bulletPosition.X -= bulletWidth / 2;
        bulletPosition.Y -= bulletHeight;

        Object::SetPosition(bulletPosition);
    }
}
