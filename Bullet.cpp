#include "Bullet.h"
#include "Vector.h"
#include "Box.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Event.h"
#include "Sprites.h"

#include <iostream>

battleCity::Bullet::Bullet(Object* ptrObj) : object(*ptrObj)
{
	sprite = SPR.getBulletSprites();
	type = "Bullet";
	id = 3;
	setSolidness(Solidness::SOFT);

	Vector pos = ptrObj->getPosition();
	Vector directionObj = ptrObj->getSight();
	float spriteObjX = ptrObj->getBox().getHorizontal();
	float spriteObjY = ptrObj->getBox().getVertical();

	// RIGHT LEFT
	if (directionObj.x == 1)
	{
		pos.y = pos.y + (spriteObjY / 2) - 2; // -2 is Centerize
		pos.x = pos.x + spriteObjX + 1;
		directionObj.x = 2;
		spriteSet(0);
	}
	else if (directionObj.x == -1)
	{
		pos.y = pos.y + (spriteObjY / 2) - 2; // -2 is Centerize
		pos.x -= 1;
		directionObj.x = -2;
		spriteSet(1);
	}
	// DOWN UP
	else if (directionObj.y == 1)
	{
		pos.x = pos.x + (spriteObjX / 2) - 2; // -2 is Centerize
		pos.y = pos.y + spriteObjY + 1;
		directionObj.y = 2;
		spriteSet(2);
	}
	else if (directionObj.y == -1)
	{
		pos.x = pos.x + (spriteObjX / 2) - 2; // -2 is Centerize
		pos.y -= 1;
		directionObj.y = -2;
		spriteSet(3);
	}

	getSpriteSize(spriteDirection, spriteX, spriteY);
	box = Box(Vector(), spriteX, spriteY);
	position = pos;
	setVelocity(directionObj);
	ptrObj = NULL;

	//std::cout << "bulletX: " << position.x << " bulletY: " << position.y << std::endl;
}

void battleCity::Bullet::out()
{
	WM.markForDelete(this);
}

void battleCity::Bullet::hit(const battleCity::EventCollision* CollisionEvent)
{
	if (((CollisionEvent->getObject1()->getType() == "Tank") ||
		(CollisionEvent->getObject2()->getType() == "Tank")) && object.getType() != "Tank") {
		WM.markForDelete(CollisionEvent->getObject1());
		WM.markForDelete(CollisionEvent->getObject2());
		return;
	}
	if (CollisionEvent->getObject1()->getType() == "Bullet" &&
		CollisionEvent->getObject2()->getType() == "Bullet")
	{
		WM.markForDelete(CollisionEvent->getObject1());
		WM.markForDelete(CollisionEvent->getObject2());
		return;
	}
	if (((CollisionEvent->getObject1()->getType() == "Player") ||
		(CollisionEvent->getObject2()->getType() == "Player")) && object.getType() != "Player") {
		WM.markForDelete(CollisionEvent->getObject1());
		WM.markForDelete(CollisionEvent->getObject2());
		return;
	}
}

void battleCity::Bullet::update()
{

}

void battleCity::Bullet::draw()
{
	drawSprite(spriteDirection, (int)position.x, (int)position.y);
}

int battleCity::Bullet::eventHandler(const Event* ptrEvent) {

	if (ptrEvent->getType() == OUT_EVENT) {
		out();
		return 1;
	}

	if (ptrEvent->getType() == COLLISION_EVENT) {
		const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (ptrEvent);
		hit(collisionEvent);
		return 1;
	}

	ptrEvent = NULL;
	// If get here, have ignored this event.
	return 0;
}

battleCity::Bullet::~Bullet()
{
	object.setBulletCount(1);
}