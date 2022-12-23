#include "PCHeader.h"

#include "Explosion.h"

namespace BattleCity::Object
{
    Explosion::Explosion()
        : Object(0, 0, { Manager::SpriteType::Explosion, Behaviour::ExplosionLarge1 })
    {
    }
}
