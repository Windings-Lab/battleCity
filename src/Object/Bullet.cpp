#include "PCHeader.h"

#include "Bullet.h"

#include "Explosion.h"
#include "SpriteManager.h"
#include "WorldManager.h"

namespace BattleCity
{
	Bullet::Bullet(Type ownerType) : Object(Type::Bullet), mOwnerType(ownerType)
	{
		mSprite = Manager::SM.SetAndGetSprite(Manager::SpriteManager::SpriteType::Tank, Behaviour::Right);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::OutOfWorld()
	{
		Manager::WM.MarkForDelete(ID);
	}

	void Bullet::Hit(EventCollision collisionEvent)
	{

	}

	void Bullet::Update()
	{
		__super::Update();
	}

	void Bullet::EventHandler(Event& myEvent)
	{
		if (myEvent.GetType() == EventType::Out)
		{
			OutOfWorld();
		}

		if (myEvent.GetType() == EventType::Collision)
		{
		}
	}
}
