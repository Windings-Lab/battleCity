#include "PCHeader.h"

#include "Explosion.h"

namespace BattleCity::Object
{
    Explosion::Explosion()
        : Object(0, 0, Type::Explosion, Manager::SpriteType::Explosion, Behaviour::ExplosionLarge1)
    {
    }

    void Explosion::Update()
    {

    }
}
