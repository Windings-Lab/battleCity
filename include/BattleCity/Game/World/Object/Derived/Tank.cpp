#include "PCHeader.h"

#include "Tank.h"

namespace BattleCity::Game::World::Object
{
    Tank::Tank(const Engine::Texture::Group& textures, std::function<Bullet*()> fireable)
	    : Object(textures), mFireable(std::move(fireable))
    {
    }

    void Tank::Fire()
    {
        mFireable.Fire(mPosition);
    }

    void Tank::SetBulletCount(int num) noexcept
    {
        mFireable.SetBulletCount(num);
    }
}
