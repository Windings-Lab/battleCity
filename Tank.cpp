#include "Tank.h"
#include "Utility.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "Event.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "Vector.h"
#include "Screen.h"

#include <iostream>
#include <vector>

Tank::Tank()
{
	speed = 1;
	change = battleCity::randomNumber(0, 3);
	id = 2;
	type = "Tank";
}

Tank::Tank(float x, float y)
{
	speed = 1;
	change = battleCity::randomNumber(0, 3);
	position.x = x;
	position.y = y;
	if (x < SCR.getBoundaryL() || x > SCR.getBoundaryR())
	{
		position.x = SCR.getBoundaryL();
	}
	if (y < SCR.getBoundaryU() || y > SCR.getBoundaryD())
	{
		position.y = SCR.getBoundaryU();
	}
	id = 2;
	type = "Tank";
}

inline void Tank::update()
{
}

inline void Tank::draw()
{
	drawSprite(spriteDirection, (int)position.x, (int)position.y);
}

int Tank::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->getType() == battleCity::STEP_EVENT)
	{
		const battleCity::EventStep* stepEvent = dynamic_cast<const battleCity::EventStep*> (eventPtr);
		if (stepEvent->getStepCount() % 250 == 0)
		{
			change++;
			if (change > 3)
				change = 0;
		}
		if (change == 0)
		{
			setVelocity(battleCity::Vector(1, 0));
		}
		if (change == 1)
		{
			setVelocity(battleCity::Vector(-1, 0));
		}
		if (change == 2)
		{
			setVelocity(battleCity::Vector(0, 1));
		}
		if (change == 3)
		{
			setVelocity(battleCity::Vector(0, -1));
		}

		spriteSet(change);
		return 1;
	}

	eventPtr = NULL;
	return 0;
}

Tank::~Tank()
{
#if DEBUG == 2
	std::cout << "Tank Destructor" << std::endl;
#endif
}