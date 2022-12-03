#include "Tank.h"
#include "Utility.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "Event.h"
#include "EventCollision.h"
#include "Explosion.h"
#include "EventStep.h"
#include "Vector.h"
#include "Screen.h"
#include "Sprites.h"
#include "EventOut.h"
#include "Bullet.h"

#include <iostream>
#include <vector>

namespace battleCity
{
	/// <summary>
	/// Object default values
	/// </summary>
	/// <param name="type">0</param>
	/// <param name="type">""</param>
	/// <param name="mCollisionPos.X">SCR.getBoundaryL()</param>
	/// <param name="mCollisionPos.Y">SCR.getBoundaryU()</param>
	/// <param name="health">1</param>
	/// <param name="constSpeed">0</param>
	/// <param name="bulletCount">1</param>
	/// <param name="solidness">Solidness::HARD</param>
	Tank::Tank()
	{
		mType = Type::Tank;

		health = 2;
		constSpeed = 1;
		bulletCount = 1;
		solidness = Solidness::Hard;
		isMovable = true;

		spriteDB = &SPR.getTankSprites();
		spriteSet();
		setSight(Vector(0, -1));

		change = 1;
		move(1, 0);
		WM.IncrementTankCount(1);
	}

	Tank::Tank(float x, float y)
	{
		mType = Type::Tank;

		initPosition(Vector(x, y));

		health = 2;
		constSpeed = 1;
		bulletCount = 1;
		solidness = Solidness::Hard;
		isMovable = true;

		spriteDB = &SPR.getTankSprites();
		spriteSet();
		setSight(Vector(0, -1));

		change = 1;
		move(1, 0);
		WM.IncrementTankCount(1);
	}

	inline void Tank::update()
	{
		int rnd = randomNumber(-30, 30);
		if (rnd == 0)
		{
			fire();
		}
		if (getSpeed() == 0.0f && (GM.stepCount + 1) % 250 == 0)
		{
			randomMove();
		}
	}

	inline void Tank::draw()
	{
		drawSprite(sprite, (int)position.X, (int)position.Y);
	}

	void Tank::fire()
	{
		if (bulletCount != 0)
		{
			std::unique_ptr<Object> bullet = std::make_unique<Bullet>(mID);
			WM.InsertObject(bullet);
			bulletCount--;
		}
	}

	void Tank::move(float x, float y)
	{
		setSight(Vector(x, y));
		if (getSight().X == 1.0f)
		{
			spriteSet(nullptr, 0);
		}
		else if (getSight().X == -1.0f)
		{
			spriteSet(nullptr, 1);
		}
		else if (getSight().Y == 1.0f)
		{
			spriteSet(nullptr, 2);
		}
		else if (getSight().Y == -1.0f)
		{
			spriteSet(nullptr, 3);
		}
		//std::cout << x << y << std::endl;
		//std::cout << "sightX: " << getSight().X << " sightY: " << getSight().Y << std::endl;
		setVelocity(Vector(x, y));
	}

	void Tank::pathFind()
	{
		isSpawnIntersects = false;
		randomMove();
	}

	void Tank::pathFind(EventCollision& collisionEvent)
	{
		auto& collisionObj = collisionEvent.GetObjectRef();
		const auto& collider = collisionEvent.GetColliderRef();

		if (collisionObj.getType() == Type::Wall || collider.getType() == Type::Wall)
		{
			if (GM.stepCount % 125 == 0)
			{
				randomMove();
			}
		}
		else if (collisionObj.getType() == Type::Tank && collisionObj.getType() == Type::Tank)
		{
			if (isSpawnIntersects)
			{
				collisionObj.setSpawnIntersection(true);
				collisionObj.setSpawnIntersection(true);
				Vector newVec = collisionObj.getPosition();
				Box b1 = collisionObj.getBox();
				Box b2 = collisionObj.getBox();
				if (boxesIntersect(b1, b2))
				{
					newVec.X = newVec.X - 32 < SCR.getBoundaryL() ? newVec.X + 32 : newVec.X - 32;
					collisionObj.setPosition(newVec);
					move(0, 0);
				}
				else
				{
					isSpawnIntersects = false;
					randomMove();
				}
			}
			if (GM.stepCount % 50 == 0)
			{
				randomMove();
			}
		}
		else if (collisionObj.getType() == Type::TankPlayer || collisionObj.getType() == Type::TankPlayer)
		{
			if (isSpawnIntersects)
			{
				collisionObj.setSpawnIntersection(true);
				collisionObj.setSpawnIntersection(true);
				Vector newVec = collisionObj.getPosition();
				Box b1 = collisionObj.getBox();
				Box b2 = collisionObj.getBox();
				if (boxesIntersect(b1, b2))
				{
					newVec.X = newVec.X - 32 < SCR.getBoundaryL() ? newVec.X + 32 : newVec.X - 32;
					collisionObj.setPosition(newVec);
					move(0, 0);
				}
				else
				{
					isSpawnIntersects = false;
					randomMove();
				}
			}
			if (GM.stepCount % 150 == 0)
			{
				randomMove();
				fire();
			}
		}
		else if (isSpawnIntersects)
		{
			isSpawnIntersects = false;
			randomMove();
		}
	}

	void Tank::randomMove()
	{
		int rnd;
		if (change == 1)
		{
			do
			{
				rnd = randomNumber(-1, 1);
			} while (rnd == getSight().X || rnd == 0);
			move(rnd, 0);
			change = 2;
		}
		else if (change == 2)
		{
			do
			{
				rnd = randomNumber(-1, 1);
			} while (rnd == getSight().Y || rnd == 0);
			move(0, rnd);
			change = 1;
		}
	}

	int Tank::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Collision)
		{
			pathFind(dynamic_cast<EventCollision&>(event));
			return 1;
		}
		if (event.GetType() == EventType::Out)
		{
			if (GM.stepCount % 10 == 0)
			{
				pathFind();
			}
			return 1;
		}
		if (event.GetType() == EventType::Step)
		{
			EventStep& stepEvent = dynamic_cast<EventStep&> (event);
			if (stepEvent.GetStepCount() % 600 == 0)
			{
				pathFind();
			}
			return 1;
		}
		return 0;
	}

	Tank::~Tank()
	{
#if DEBUG == 2
		std::cout << "Tank Destructor" << std::endl;
#endif
		if(GM.gameOver) return; // TODO: Fix
		WM.IncrementTankCount(-1);
		WM.IncrementKillCount(1);
		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(true);
		newExp->setPosition(position);

		WM.InsertObject(newExp);
	}
}