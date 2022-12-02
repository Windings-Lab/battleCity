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

	void PhoenixAndFlag::setGameOver(EventCollision& collisionEvent)
	{
		const auto& collisionObj = collisionEvent.GetObjectRef();
		const auto& collider = collisionEvent.GetColliderRef();
		if (collider.getType() == Type::Bullet || collisionObj.getType() == Type::Bullet)
		{
			gameOver = true;
			spriteSet(nullptr, 1);
			GM.setStepCount(1);
			WM.SetGameOverState();
			return;
		}
	}

	int PhoenixAndFlag::EventHandler(Event event)
	{
		if (!gameOver)
		{
			if (event.GetType() == EventType::Collision)
			{
				setGameOver(dynamic_cast<EventCollision&>(event));
				return 1;
			}
		}
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