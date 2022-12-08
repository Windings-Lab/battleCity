#include "PCHeader.h"

#include "Bullet.h"
#include "SpriteManager.h"
#include "WorldManager.h"

namespace BattleCity::Object
{
	Bullet::Bullet(Type ownerType) : Object(Type::Bullet), mOwnerType(ownerType)
	{
		mSprite = Manager::SM.SetAndGetSprite(Manager::SpriteType::Tank, Behaviour::Right);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Update()
	{
		__super::Update();
	}
}
