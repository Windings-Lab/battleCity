#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::Update()
    {
        Object::Update();
        mPosition = mMovable.GetSpeedDirection() + mPosition;
    }

    void Bullet::SetSpeed(Speed speed) noexcept
    {
        mMovable.SetSpeed(speed);
    }
    void Bullet::SetDirection(Direction direction) noexcept
    {
        mMovable.SetDirection(direction);
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
