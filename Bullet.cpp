#include "Bullet.h"
#include "Explosion.h"
#include "GameManager.h"
#include "WorldManager.h"

namespace battleCity
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

	void Bullet::Draw()
	{
		// drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}

	void Bullet::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Out)
		{
			OutOfWorld();
		}

		if (event.GetType() == EventType::Collision)
		{
			Hit(dynamic_cast<EventCollision&>(event));
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
