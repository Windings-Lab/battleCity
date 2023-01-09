#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Game::World::Object
{
    Bullet::Bullet(const Engine::Texture::Group& textures)
	    : Object(textures)
		, mCollider(*this)
    {
	    
    }

    void Bullet::Update()
    {

    }

    void Bullet::ResolveCollision(const Object& obj)
    {
        //mCollider.ResolveCollisions(o)
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
