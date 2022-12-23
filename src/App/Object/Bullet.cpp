#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Object
{
	Bullet::Bullet(Type ownerType)
		: Object(0, 0, { Manager::SpriteType::Bullet, Behaviour::Up })
		, mOwnerType(ownerType)
	{	}
}
