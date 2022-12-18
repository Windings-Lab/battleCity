#include "PCHeader.h"

#include "Bullet.h"

namespace BattleCity::Object
{
	Bullet::Bullet(Type ownerType)
		: Object(0, 0, Type::Bullet, Manager::SpriteType::Bullet, Behaviour::Up), mOwnerType(ownerType)
	{
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Update()
	{

	}
}
