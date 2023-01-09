#include "PCHeader.h"

#include "Tank.h"

namespace BattleCity::Game::World::Object
{
    Tank::Tank(const Engine::Texture::Group& textures, std::function<std::shared_ptr<Bullet>()> fireable)
	    : Object(textures), mFireable(std::move(fireable))
    {
    }

    void Tank::SetSpeed(Speed s) noexcept
    {
        mMovable.SetSpeed(s);
    }
    void Tank::SetDirection(Direction d) noexcept
    {
        mMovable.SetDirection(d);
    }

    void Tank::Fire()
    {
        mFireable.Fire(GetBulletSpawnPositon(), mMovable.GetDirection());
    }
    void Tank::SetBulletCount(int num) noexcept
    {
        mFireable.SetBulletCount(num);
    }

    Position Tank::GetBulletSpawnPositon() const noexcept
    {
        int tankWidth;
        int tankHeight;

        GetTextureSize(tankWidth, tankHeight);

        Position bulletPosition(mPosition);
        bulletPosition.X += tankWidth / 2;

        return bulletPosition;
    }
}
