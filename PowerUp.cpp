#include "PowerUp.h"
#include "EventCollision.h"
#include "Utility.h"
#include "WorldManager.h"
#include "Screen.h"

#include <iostream>

battleCity::PowerUp::PowerUp()
{
	mType = Type::PowerUp;

	int rnd = randomNumber(0, WM.GetPowerUpPositions().size() - 1);
	indexX = WM.GetPowerUpPositions()[rnd][0];
	indexY = WM.GetPowerUpPositions()[rnd][1];
	initPosition(Vector(indexX, indexY));

	health = 1;
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::Soft;

	spriteDB = &SPR.getPowerUpSprites();
	spriteSet(nullptr, 0);
}

battleCity::PowerUp::PowerUp(int giveHealth)
{
	mType = Type::PowerUp;

	int rnd = randomNumber(0, WM.GetPowerUpPositions().size() - 1);
	indexX = WM.GetPowerUpPositions()[rnd][0];
	indexY = WM.GetPowerUpPositions()[rnd][1];
	initPosition(Vector(indexX, indexY));

	health = giveHealth;
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::Soft;

	spriteDB = &SPR.getPowerUpSprites();
	spriteSet(nullptr, 0);
}

void battleCity::PowerUp::draw()
{
	drawSprite(sprite, (int)position.X, (int)position.Y);
}

void battleCity::PowerUp::makePowerUp(const battleCity::EventCollision* collisionEvent)
{
	auto& collisionObj = collisionEvent->GetObjectRef();
	if	(collisionObj.getType() == Type::TankPlayer)
	{
		collisionObj.setHealth(health);
		WM.MarkForDelete(mID);
		WM.SetPowerUpisTakedToTrue();
	}
}

int battleCity::PowerUp::eventHandler(const Event* ptrEvent)
{
	if (ptrEvent->GetType() == EventType::Collision)
	{
		const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (ptrEvent);
		makePowerUp(collisionEvent);
		collisionEvent = nullptr;
		ptrEvent = nullptr;
		return 1;
	}

	return 0;
}

battleCity::PowerUp::~PowerUp()
{
	WM.SetPowerUpToFalse();
}