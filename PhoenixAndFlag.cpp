#include "PhoenixAndFlag.h"
#include "Sprites.h"
#include "Event.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "GameManager.h"

#include <iostream>

namespace battleCity
{
	PhoenixAndFlag::PhoenixAndFlag(float x, float y)
	{
		mType = Type::PhoenixAndFlag;

		position.X = x;
		position.Y = y;

		health = 0;
		constSpeed = 0;
		bulletCount = 0;
		solidness = Solidness::Soft;

		gameOver = false;

		spriteDB = new std::vector<Sprite*>;
		(*spriteDB).push_back(&SPR.getPhoenixSprite());
		(*spriteDB).push_back(&SPR.getWhiteFlagSprite());

		spriteSet(nullptr, 0);
	}


	void PhoenixAndFlag::draw()
	{
		drawSprite(sprite, (int)position.X, (int)position.Y);
	}

	void PhoenixAndFlag::setGameOver(const EventCollision* CollisionEvent)
	{
		if (CollisionEvent->GetColliderID()->getType() == Type::Bullet ||
			CollisionEvent->GetObjectID()->getType() == Type::Bullet)
		{
			gameOver = true;
			spriteSet(nullptr, 1);
			GM.setStepCount(1);
			WM.SetGameOverState();
			return;
		}
	}

	int PhoenixAndFlag::eventHandler(const Event* eventPtr)
	{
		if (!gameOver)
		{
			if (eventPtr->GetType() == EventType::Collision)
			{
				const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (eventPtr);
				setGameOver(collisionEvent);
				collisionEvent = nullptr;
				eventPtr = nullptr;
				return 1;
			}
		}
		eventPtr = nullptr;
		return 0;
	}

	PhoenixAndFlag::~PhoenixAndFlag()
	{
		for (size_t i = 0; i < spriteDB->size(); i++)
		{
			spriteDB->at(i) = nullptr;
		}
		delete spriteDB;
		spriteDB = nullptr;
	}
}