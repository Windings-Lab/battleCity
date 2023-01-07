#include "PCHeader.h"

#include "Tank.h"

namespace BattleCity::Game::World::Object
{
    Tank::Tank(const Engine::Texture::Group& textures, std::function<std::shared_ptr<Object>()> fireable)
	    : Object(textures), mFireable(std::move(fireable))
    {
    }

    void Tank::Fire()
    {
        mFireable.Fire(GetBulletSpawnPositon());
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

        Position bulletPosition(mPosition.X, mPosition.Y);
        bulletPosition.X += tankWidth / 2;

        return bulletPosition;
    }
}
