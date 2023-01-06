#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::Update()
    {
        mPosition.Y--;
    }
}
