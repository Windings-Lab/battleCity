#include "Tank.h"
#include "Utility.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "Event.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "Vector.h"
#include "Screen.h"
#include "Sprites.h"
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

	spriteDB = SPR.getTankSprites();
	spriteSet(0, 3);
	setSight(Vector(0, -1));

	change = battleCity::randomNumber(0, 3);
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

	spriteDB = SPR.getTankSprites();
	spriteSet(0, 3);
	setSight(Vector(0, -1));

	change = battleCity::randomNumber(0, 3);
}

inline void battleCity::Tank::update()
{
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
	setVelocity(Vector(x, y));
}

int battleCity::Tank::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->getType() == battleCity::STEP_EVENT)
	{
		const battleCity::EventStep* stepEvent = dynamic_cast<const battleCity::EventStep*> (eventPtr);
		unsigned int loopStep = stepEvent->getStepCount();
		if (loopStep % 250 == 0)
		{
			change++;
			if (change > 3)
				change = 0;
			change = 1;
			if (change == 0)
			{
				move(1, 0);
			}
			if (change == 1)
			{
				move(-1, 0);
			}
			if (change == 2)
			{
				move(0, 1);
			}
			if (change == 3)
			{
				move(0, -1);
			}
			fire();
		}

		spriteSet(0, change);
		return 1;
	}

	eventPtr = NULL;
	return 0;
}

battleCity::Tank::~Tank()
{
#if DEBUG == 2
	std::cout << "Tank Destructor" << std::endl;
#endif
}