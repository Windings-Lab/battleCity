#include "Bullet.h"
#include "Explosion.h"
#include "GameManager.h"
#include "WorldManager.h"

namespace BattleCity
{
	Bullet::Bullet(Type ownerType) : Object(Type::Bullet), mOwnerType(ownerType)
	{
	}

	void Bullet::OutOfWorld()
	{
		WM.MarkForDelete(ID);
	}

	void Bullet::Hit(EventCollision collisionEvent)
	{

	}

	void Bullet::Update()
	{

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

	Bullet::~Bullet()
	{
		if (GM.GetGameOver()) return; // TODO: Fix
		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(false);
		newExp->SetPosition(X(), Y());

		WM.InsertObject(newExp);
	}
}
