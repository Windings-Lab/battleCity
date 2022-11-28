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

/// <summary>
/// Object default values
/// </summary>
/// <param name="id">0</param>
/// <param name="type">""</param>
/// <param name="position.x">SCR.getBoundaryL()</param>
/// <param name="position.y">SCR.getBoundaryU()</param>
/// <param name="health">1</param>
/// <param name="constSpeed">0</param>
/// <param name="bulletCount">1</param>
/// <param name="solidness">Solidness::HARD</param>
battleCity::Tank::Tank()
{
	id = 2;
	type = "Tank";

	health = 2;
	constSpeed = 1;
	bulletCount = 1;
	solidness = Solidness::HARD;

	spriteDB = &SPR.getTankSprites();
	spriteSet();
	setSight(Vector(0, -1));

	change = 1;
	move(1, 0);
	WM.setTankCount(1);
}

battleCity::Tank::Tank(float x, float y)
{
	id = 2;
	type = "Tank";

	initPosition(Vector(x, y));

	health = 2;
	constSpeed = 1;
	bulletCount = 1;
	solidness = Solidness::HARD;

	spriteDB = &SPR.getTankSprites();
	spriteSet();
	setSight(Vector(0, -1));

	change = 1;
	move(1, 0);
	WM.setTankCount(1);
}

inline void battleCity::Tank::update()
{
	int rnd = battleCity::randomNumber(-30, 30);
	if (rnd == 0)
	{
		fire();
	}
	if (getSpeed() == 0 && (GM.stepCount + 1) % 250 == 0)
	{
		randomMove();
	}
}

inline void battleCity::Tank::draw()
{
	drawSprite(sprite, (int)position.x, (int)position.y);
}

void battleCity::Tank::fire()
{
	if (bulletCount != 0)
	{
		Bullet* newBullet = new Bullet(*this);
		bulletCount--;
	}
}

void battleCity::Tank::move(float x, float y)
{
	setSight(Vector(x, y));
	if (getSight().x == 1)
	{
		spriteSet(nullptr, 0);
	}
	else if (getSight().x == -1)
	{
		spriteSet(nullptr, 1);
	}
	else if (getSight().y == 1)
	{
		spriteSet(nullptr, 2);
	}
	else if (getSight().y == -1)
	{
		spriteSet(nullptr, 3);
	}
	//std::cout << x << y << std::endl;
	//std::cout << "sightX: " << getSight().x << " sightY: " << getSight().y << std::endl;
	setVelocity(Vector(x, y));
}

void battleCity::Tank::pathFind(const battleCity::EventCollision* CollisionEvent)
{
	if (CollisionEvent == nullptr)
	{
		isSpawnIntersects = false;
		randomMove();
	}
	else if (CollisionEvent->getObject1()->getType() == "Wall" || CollisionEvent->getObject2()->getType() == "Wall")
	{
		if (GM.stepCount % 125 == 0)
		{
			randomMove();
		}
	}
	else if (CollisionEvent->getObject1()->getType() == "Tank" && CollisionEvent->getObject2()->getType() == "Tank")
	{
		if (isSpawnIntersects)
		{
			/*Vector newVec = CollisionEvent->getObject1()->getPosition();
			Vector sight1 = CollisionEvent->getObject1()->getSight();
			Vector sight2 = CollisionEvent->getObject2()->getSight();

			if (sight1.x == 1 && sight2.x == 1)
			{
				newVec.x -= 16;
				CollisionEvent->getObject1()->setPosition(newVec);
			}
			else if (sight1.x == -1 && sight2.x == -1)
			{
				newVec.x += 16;
				CollisionEvent->getObject1()->setPosition(newVec);
			}
			else if ((sight1.x == 1 && sight2.x == -1) || (sight2.x == 1 && sight1.x == -1))
			{
				newVec.x -= 16;
				CollisionEvent->getObject1()->setPosition(newVec);
				newVec.x += 16;
				CollisionEvent->getObject2()->setPosition(newVec);
			}
			else
			{
				newVec.x = newVec.x - 16 < SCR.getBoundaryL() ? newVec.x + 16 : newVec.x - 16;
				CollisionEvent->getObject1()->setPosition(newVec);
			}*/
			CollisionEvent->getObject1()->setSpawnIntersection(true);
			CollisionEvent->getObject2()->setSpawnIntersection(true);
			Vector newVec = CollisionEvent->getObject1()->getPosition();
			Box b1 = CollisionEvent->getObject1()->getBox();
			Box b2 = CollisionEvent->getObject2()->getBox();
			if (boxesIntersect(b1, b2))
			{
				newVec.x = newVec.x - 32 < SCR.getBoundaryL() ? newVec.x + 32 : newVec.x - 32;
				CollisionEvent->getObject1()->setPosition(newVec);
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
	else if (CollisionEvent->getObject1()->getType() == "Player" || CollisionEvent->getObject2()->getType() == "Player")
	{
		if (isSpawnIntersects)
		{
			CollisionEvent->getObject1()->setSpawnIntersection(true);
			CollisionEvent->getObject2()->setSpawnIntersection(true);
			Vector newVec = CollisionEvent->getObject1()->getPosition();
			Box b1 = CollisionEvent->getObject1()->getBox();
			Box b2 = CollisionEvent->getObject2()->getBox();
			if (boxesIntersect(b1, b2))
			{
				newVec.x = newVec.x - 32 < SCR.getBoundaryL() ? newVec.x + 32 : newVec.x - 32;
				CollisionEvent->getObject1()->setPosition(newVec);
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

void battleCity::Tank::randomMove()
{
	int rnd;
	if (change == 1)
	{
		do
		{
			rnd = battleCity::randomNumber(-1, 1);
		} while (rnd == getSight().x || rnd == 0);
		move(rnd, 0);
		change = 2;
	}
	else if (change == 2)
	{
		do
		{
			rnd = battleCity::randomNumber(-1, 1);
		} while (rnd == getSight().y || rnd == 0);
		move(0, rnd);
		change = 1;
	}
}

int battleCity::Tank::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->getType() == battleCity::COLLISION_EVENT)
	{
		const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (eventPtr);
		pathFind(collisionEvent);
		collisionEvent = nullptr;
		eventPtr = nullptr;
		return 1;
	}
	if (eventPtr->getType() == battleCity::OUT_EVENT)
	{
		if (GM.stepCount % 10 == 0)
		{
			pathFind();
		}
		eventPtr = nullptr;
		return 1;
	}
	if (eventPtr->getType() == battleCity::STEP_EVENT)
	{
		const EventStep* stepEvent = dynamic_cast<const EventStep*> (eventPtr);
		if (stepEvent->getStepCount() % 600 == 0)
		{
			pathFind();
		}
		stepEvent = nullptr;
		eventPtr = nullptr;
		return 1;
	}
	eventPtr = nullptr;
	return 0;
}

battleCity::Tank::~Tank()
{
#if DEBUG == 2
	std::cout << "Tank Destructor" << std::endl;
#endif
	WM.setTankCount(-1);
	WM.setKillCount(1);
	Explosion* newExp = new Explosion(true);
	newExp->setPosition(this->position);
	newExp = nullptr;
}