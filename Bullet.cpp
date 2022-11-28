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

battleCity::Bullet::Bullet(Object& ptrObj) : object(ptrObj)
{
	id = 3;
	type = "Bullet";

	health = 1;
	constSpeed = 2;
	bulletCount = 0;
	solidness = Solidness::SOFT;

	spriteDB = &SPR.getBulletSprites();

	initBullet(object);
	//std::cout << "bulletX: " << position.x << " bulletY: " << position.y << std::endl;
}

void battleCity::Bullet::initBullet(const Object& ptrObj)
{
	Vector pos = ptrObj.getPosition();
	Vector directionObj = ptrObj.getSight();
	float spriteObjX = ptrObj.getBox().getHorizontal();
	float spriteObjY = ptrObj.getBox().getVertical();

	// RIGHT LEFT
	if (directionObj.x == 1)
	{
		pos.y = pos.y + (spriteObjY / 2) - 2; // -2 is Centerize
		pos.x = pos.x + spriteObjX;
		directionObj.x = constSpeed;
		spriteSet(nullptr, 0);
		setSight(Vector(1, 0));
	}
	else if (directionObj.x == -1)
	{
		pos.y = pos.y + (spriteObjY / 2) - 2; // -2 is Centerize
		directionObj.x = -constSpeed;
		spriteSet(nullptr, 1);
		setSight(Vector(-1, 0));
	}
	// DOWN UP
	else if (directionObj.y == 1)
	{
		pos.x = pos.x + (spriteObjX / 2) - 2; // -2 is Centerize
		pos.y = pos.y + spriteObjY;
		directionObj.y = constSpeed;
		spriteSet(nullptr, 2);
		setSight(Vector(0, 1));
	}
	else if (directionObj.y == -1)
	{
		pos.x = pos.x + (spriteObjX / 2) - 2; // -2 is Centerize
		directionObj.y = -constSpeed;
		spriteSet(nullptr, 3);
		setSight(Vector(0, -1));
	}

	position = pos;
	setVelocity(directionObj);
	objectID = object.getWorldID();
	objectType = object.getType();
}

void battleCity::Bullet::out()
{
	WM.markForDelete(this);
}

void battleCity::Bullet::hit(const battleCity::EventCollision* CollisionEvent)
{
	if (health != 0)
	{
		if (objectID != CollisionEvent->getObject1()->getWorldID()
			&&
			objectID != CollisionEvent->getObject2()->getWorldID())
		{
			if ((CollisionEvent->getObject2()->getType() == "Tank" ||
				CollisionEvent->getObject1()->getType() == "Tank") && objectType == "Tank")
			{
				WM.markForDelete(this);
				return;
			}
			if ((CollisionEvent->getObject2()->getType() == "PowerUp" ||
				CollisionEvent->getObject1()->getType() == "PowerUp"))
			{
				return;
			}
			WM.markForDelete(CollisionEvent->getObject1());
			WM.markForDelete(CollisionEvent->getObject2());
			return;
		}
	}
}

void battleCity::Bullet::draw()
{
	drawSprite(sprite, (int)position.x, (int)position.y);
}

int battleCity::Bullet::eventHandler(const Event* ptrEvent) {

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

battleCity::Bullet::~Bullet()
{
	object.setBulletCount(1);
	position.x -= 5;
	Explosion* newExp = new Explosion(false);
	newExp->setPosition(this->position);
	newExp = nullptr;
}
