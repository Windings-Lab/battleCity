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
	/// <param name="mCollisionPos.x">SCR.getBoundaryL()</param>
	/// <param name="mCollisionPos.y">SCR.getBoundaryU()</param>
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

		spriteDB = &SPR.getTankSprites();
		spriteSet();
		setSight(Vector(0, -1));

		change = 1;
		move(1, 0);
		WM.SetTankCount(1);
	}

	Tank::Tank(float x, float y)
	{
		mType = Type::Tank;

		initPosition(Vector(x, y));

		health = 2;
		constSpeed = 1;
		bulletCount = 1;
		solidness = Solidness::Hard;

		spriteDB = &SPR.getTankSprites();
		spriteSet();
		setSight(Vector(0, -1));

		change = 1;
		move(1, 0);
		WM.SetTankCount(1);
	}

	inline void Tank::update()
	{
		int rnd = randomNumber(-30, 30);
		if (rnd == 0)
		{
			fire();
		}
		if (getSpeed() == 0 && (GM.stepCount + 1) % 250 == 0)
		{
			randomMove();
		}
	}

	inline void Tank::draw()
	{
		drawSprite(sprite, (int)position.x, (int)position.y);
	}

	void Tank::fire()
	{
		if (bulletCount != 0)
		{
			Bullet* newBullet = new Bullet(*this);
			bulletCount--;
		}
	}

	void Tank::move(float x, float y)
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

	void Tank::pathFind(const EventCollision* CollisionEvent)
	{
		if (CollisionEvent == nullptr)
		{
			isSpawnIntersects = false;
			randomMove();
		}
		else if (CollisionEvent->GetObjectID()->getType() == Type::Wall || CollisionEvent->GetColliderID()->getType() == Type::Wall)
		{
			if (GM.stepCount % 125 == 0)
			{
				randomMove();
			}
		}
		else if (CollisionEvent->GetObjectID()->getType() == Type::Tank && CollisionEvent->GetColliderID()->getType() == Type::Tank)
		{
			if (isSpawnIntersects)
			{
				/*Vector newVec = CollisionEvent->GetObjectID()->GetCollisionPos();
				Vector sight1 = CollisionEvent->GetObjectID()->getSight();
				Vector sight2 = CollisionEvent->GetColliderID()->getSight();

				if (sight1.x == 1 && sight2.x == 1)
				{
					newVec.x -= 16;
					CollisionEvent->GetObjectID()->SetCollisionPos(newVec);
				}
				else if (sight1.x == -1 && sight2.x == -1)
				{
					newVec.x += 16;
					CollisionEvent->GetObjectID()->SetCollisionPos(newVec);
				}
				else if ((sight1.x == 1 && sight2.x == -1) || (sight2.x == 1 && sight1.x == -1))
				{
					newVec.x -= 16;
					CollisionEvent->GetObjectID()->SetCollisionPos(newVec);
					newVec.x += 16;
					CollisionEvent->GetColliderID()->SetCollisionPos(newVec);
				}
				else
				{
					newVec.x = newVec.x - 16 < SCR.getBoundaryL() ? newVec.x + 16 : newVec.x - 16;
					CollisionEvent->GetObjectID()->SetCollisionPos(newVec);
				}*/
				CollisionEvent->GetObjectID()->setSpawnIntersection(true);
				CollisionEvent->GetColliderID()->setSpawnIntersection(true);
				Vector newVec = CollisionEvent->GetObjectID()->getPosition();
				Box b1 = CollisionEvent->GetObjectID()->getBox();
				Box b2 = CollisionEvent->GetColliderID()->getBox();
				if (boxesIntersect(b1, b2))
				{
					newVec.x = newVec.x - 32 < SCR.getBoundaryL() ? newVec.x + 32 : newVec.x - 32;
					CollisionEvent->GetObjectID()->setPosition(newVec);
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
		else if (CollisionEvent->GetObjectID()->getType() == Type::TankPlayer || CollisionEvent->GetColliderID()->getType() == Type::TankPlayer)
		{
			if (isSpawnIntersects)
			{
				CollisionEvent->GetObjectID()->setSpawnIntersection(true);
				CollisionEvent->GetColliderID()->setSpawnIntersection(true);
				Vector newVec = CollisionEvent->GetObjectID()->getPosition();
				Box b1 = CollisionEvent->GetObjectID()->getBox();
				Box b2 = CollisionEvent->GetColliderID()->getBox();
				if (boxesIntersect(b1, b2))
				{
					newVec.x = newVec.x - 32 < SCR.getBoundaryL() ? newVec.x + 32 : newVec.x - 32;
					CollisionEvent->GetObjectID()->setPosition(newVec);
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
			} while (rnd == getSight().x || rnd == 0);
			move(rnd, 0);
			change = 2;
		}
		else if (change == 2)
		{
			do
			{
				rnd = randomNumber(-1, 1);
			} while (rnd == getSight().y || rnd == 0);
			move(0, rnd);
			change = 1;
		}
	}

	int Tank::eventHandler(const Event* eventPtr)
	{
		if (eventPtr->GetType() == EventType::Collision)
		{
			const EventCollision* collisionEvent = dynamic_cast <const EventCollision*> (eventPtr);
			pathFind(collisionEvent);
			collisionEvent = nullptr;
			eventPtr = nullptr;
			return 1;
		}
		if (eventPtr->GetType() == EventType::Out)
		{
			if (GM.stepCount % 10 == 0)
			{
				pathFind();
			}
			eventPtr = nullptr;
			return 1;
		}
		if (eventPtr->GetType() == EventType::Step)
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

	Tank::~Tank()
	{
#if DEBUG == 2
		std::cout << "Tank Destructor" << std::endl;
#endif
		WM.SetTankCount(-1);
		WM.SetKillCount(1);
		Explosion* newExp = new Explosion(true);
		newExp->setPosition(this->position);
		newExp = nullptr;
	}
}