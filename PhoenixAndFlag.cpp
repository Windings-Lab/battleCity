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

		mPosition.X = x;
		mPosition.Y = y;

		mHealth = 0;
		mConstSpeed = 0;
		mBulletCount = 0;
		mSolidness = Solidness::Soft;

		gameOver = false;

		spriteDB = new std::vector<Sprite*>;
		(*spriteDB).push_back(&SPR.getPhoenixSprite());
		(*spriteDB).push_back(&SPR.getWhiteFlagSprite());

		SpriteSet(nullptr, 0);
	}


	void PhoenixAndFlag::Draw()
	{
		drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}

	void PhoenixAndFlag::setGameOver(EventCollision& collisionEvent)
	{
		const auto& collisionObj = collisionEvent.GetObjectRef();
		const auto& collider = collisionEvent.GetColliderRef();
		if (collider.GetType() == Type::Bullet || collisionObj.GetType() == Type::Bullet)
		{
			gameOver = true;
			SpriteSet(nullptr, 1);
			GM.SetGameOverState();
		}
	}

	int PhoenixAndFlag::EventHandler(Event& event)
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