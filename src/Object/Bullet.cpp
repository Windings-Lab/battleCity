#include "PCHeader.h"

#include "Bullet.h"

#include "Explosion.h"
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

	void Bullet::OutOfWorld()
	{
		Manager::WM.MarkForDelete(ID);
	}

	void Bullet::Hit(Event::EventCollision collisionEvent)
	{

	}

	void Bullet::Update()
	{
		__super::Update();
	}

	void Bullet::EventHandler(Event::Event& myEvent)
	{
		if (myEvent.GetType() == Event::Type::Out)
		{
			OutOfWorld();
		}

		if (myEvent.GetType() == Event::Type::Collision)
		{
		}
	}
}
