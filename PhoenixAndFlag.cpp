#include "PhoenixAndFlag.h"
#include "Sprites.h"
#include "Event.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "GameManager.h"

#include <iostream>

battleCity::PhoenixAndFlag::PhoenixAndFlag(float x, float y)
{
	id = 5;
	type = "Phoenix";

	position.x = x;
	position.y = y;

	health = 0;
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::SOFT;

	gameOver = false;

	spriteDB = new std::vector<Sprite*>;
	(*spriteDB).push_back(&SPR.getPhoenixSprite());
	(*spriteDB).push_back(&SPR.getWhiteFlagSprite());

	spriteSet(0, 0);
}


void battleCity::PhoenixAndFlag::draw()
{
	drawSprite(sprite, (int)position.x, (int)position.y);
}

void battleCity::PhoenixAndFlag::setGameOver(const battleCity::EventCollision* CollisionEvent)
{
	if (CollisionEvent->getObject2()->getType() == "Bullet" ||
		CollisionEvent->getObject1()->getType() == "Bullet")
	{
		gameOver = true;
		spriteSet(0, 1);
		GM.setStepCount(1);
		WM.setGameOverState();
		return;
	}
}

int battleCity::PhoenixAndFlag::eventHandler(const Event* eventPtr)
{
	if (!gameOver)
	{
		if (eventPtr->getType() == battleCity::COLLISION_EVENT)
		{
			const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (eventPtr);
			setGameOver(collisionEvent);
			collisionEvent = NULL;
			eventPtr = NULL;
			return 1;
		}
	}
	eventPtr = NULL;
	return 0;
}

battleCity::PhoenixAndFlag::~PhoenixAndFlag()
{
	for (size_t i = 0; i < spriteDB->size(); i++)
	{
		spriteDB->at(i) = NULL;
	}
	delete spriteDB;
	spriteDB = NULL;
}