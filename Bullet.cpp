#include "Bullet.h"
#include "Vector.h"
#include "Box.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "Explosion.h"
#include "GameManager.h"
#include "Event.h"
#include "Sprites.h"

#include <iostream>

namespace battleCity
{
	Bullet::Bullet(Object& ptrObj) : object(ptrObj)
	{
		mType = Type::Bullet;

		health = 1;
		constSpeed = 2;
		bulletCount = 0;
		solidness = Solidness::Soft;

		spriteDB = &SPR.getBulletSprites();

		initBullet(object);
		//std::cout << "bulletX: " << mCollisionPos.X << " bulletY: " << mCollisionPos.Y << std::endl;
	}

	void Bullet::initBullet(const Object& ptrObj)
	{
		Vector pos = ptrObj.getPosition();
		Vector directionObj = ptrObj.getSight();
		float spriteObjX = ptrObj.getBox().getHorizontal();
		float spriteObjY = ptrObj.getBox().getVertical();

		// RIGHT LEFT
		if (directionObj.X == 1)
		{
			pos.Y = pos.Y + (spriteObjY / 2) - 2; // -2 is Centerize
			pos.X = pos.X + spriteObjX;
			directionObj.X = constSpeed;
			spriteSet(nullptr, 0);
			setSight(Vector(1, 0));
		}
		else if (directionObj.X == -1)
		{
			pos.Y = pos.Y + (spriteObjY / 2) - 2; // -2 is Centerize
			directionObj.X = -constSpeed;
			spriteSet(nullptr, 1);
			setSight(Vector(-1, 0));
		}
		// DOWN UP
		else if (directionObj.Y == 1)
		{
			pos.X = pos.X + (spriteObjX / 2) - 2; // -2 is Centerize
			pos.Y = pos.Y + spriteObjY;
			directionObj.Y = constSpeed;
			spriteSet(nullptr, 2);
			setSight(Vector(0, 1));
		}
		else if (directionObj.Y == -1)
		{
			pos.X = pos.X + (spriteObjX / 2) - 2; // -2 is Centerize
			directionObj.Y = -constSpeed;
			spriteSet(nullptr, 3);
			setSight(Vector(0, -1));
		}

		position = pos;
		setVelocity(directionObj);
		objectID = object.GetID();
		objectType = object.getType();
	}

	void Bullet::out()
	{
		WM.MarkForDelete(this);
	}

	void Bullet::hit(const EventCollision* CollisionEvent)
	{
		if (health != 0)
		{
			if (objectID != CollisionEvent->GetObjectID()->GetID()
				&&
				objectID != CollisionEvent->GetColliderID()->GetID())
			{
				if ((CollisionEvent->GetColliderID()->getType() == Type::Tank ||
					CollisionEvent->GetObjectID()->getType() == Type::Tank) && objectType == Type::Tank)
				{
					WM.MarkForDelete(this);
					return;
				}
				if ((CollisionEvent->GetColliderID()->getType() == Type::PowerUp ||
					CollisionEvent->GetObjectID()->getType() == Type::PowerUp))
				{
					return;
				}
				WM.MarkForDelete(CollisionEvent->GetObjectID());
				WM.MarkForDelete(CollisionEvent->GetColliderID());
				return;
			}
		}
	}

	void Bullet::draw()
	{
		drawSprite(sprite, (int)position.X, (int)position.Y);
	}

	int Bullet::eventHandler(const Event* ptrEvent) {

		if (ptrEvent->GetType() == EventType::Out) {
			out();
			return 1;
		}

		if (ptrEvent->GetType() == EventType::Collision) {
			const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (ptrEvent);
			hit(collisionEvent);
			collisionEvent = nullptr;
			return 1;
		}

		ptrEvent = nullptr;
		// If get here, have ignored this event.
		return 0;
	}

	Bullet::~Bullet()
	{
		object.setBulletCount(1);
		position.X -= 5;
		Explosion* newExp = new Explosion(false);
		newExp->setPosition(this->position);
		newExp = nullptr;
	}
}
