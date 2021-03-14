#include "PowerUp.h"
#include "EventCollision.h"
#include "Utility.h"
#include "WorldManager.h"
#include "Screen.h"

#include <iostream>

battleCity::PowerUp::PowerUp()
{
	id = 7;
	type = "PowerUp";

	int rnd = randomNumber(0, WM.getPowerUpPositions().size() - 1);
	indexX = WM.getPowerUpPositions()[rnd][0];
	indexY = WM.getPowerUpPositions()[rnd][1];
	initPosition(Vector(indexX, indexY));

	health = 1;
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::SOFT;

	spriteDB = &SPR.getPowerUpSprites();
	spriteSet(0, 0);
}

battleCity::PowerUp::PowerUp(int giveHealth)
{
	id = 7;
	type = "PowerUp";

	int rnd = randomNumber(0, WM.getPowerUpPositions().size() - 1);
	indexX = WM.getPowerUpPositions()[rnd][0];
	indexY = WM.getPowerUpPositions()[rnd][1];
	initPosition(Vector(indexX, indexY));

	health = giveHealth;
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::SOFT;

	spriteDB = &SPR.getPowerUpSprites();
	spriteSet(0, 0);
}

void battleCity::PowerUp::draw()
{
	drawSprite(sprite, (int)position.x, (int)position.y);
}

void battleCity::PowerUp::makePowerUp(const battleCity::EventCollision* CollisionEvent)
{
	if	(CollisionEvent->getObject1()->getType() == "Player")
	{
		CollisionEvent->getObject1()->setHealth(health);
		WM.markForDelete(this);
		WM.setPowerUpisTakedToTrue();
	}
}

int battleCity::PowerUp::eventHandler(const Event* ptrEvent)
{
	if (ptrEvent->getType() == battleCity::COLLISION_EVENT)
	{
		const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (ptrEvent);
		makePowerUp(collisionEvent);
		collisionEvent = NULL;
		ptrEvent = NULL;
		return 1;
	}

	return 0;
}

battleCity::PowerUp::~PowerUp()
{
	WM.setPowerUpToFalse();
}