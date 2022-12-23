#include "PCHeader.h"

#include "Tank.h"

namespace BattleCity::Object
{
    Tank::Tank(int x, int y)
	    : Object(x, y, {Manager::SpriteType::TankNPC, Behaviour::Up})
    {
    }
}
