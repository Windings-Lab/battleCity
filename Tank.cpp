#include "Tank.h"
#include "EventStep.h"
#include "WorldManager.h"

Tank::Tank()
{
	speed = 1;
	change = 3;
	id = 2;
	type = "Tank";
}

Tank::Tank(int x, int y)
{
	speed = 1;
	change = 3;
	position.x = x;
	position.y = y;
	id = 2;
	type = "Tank";
}

inline void Tank::update()
{
	direction.x = 0;
	direction.y = 0;
}

inline void Tank::draw()
{
	drawSprite(sprite[0], (int)position.x, (int)position.y);
}

int Tank::eventHandler(const battleCity::Event* eventPtr)
{
	if (eventPtr->getType() == battleCity::STEP_EVENT)
	{
		const battleCity::EventStep* stepEvent = dynamic_cast<const battleCity::EventStep*> (eventPtr);
		if (stepEvent->getStepCount() % 250 == 0)
		{
			change++;
			if (change > 4)
				change = 1;
		}
		if (change == 1)
		{
			WM.moveObject(this, battleCity::Vector(position.x + 1, position.y));
		}
		if (change == 2)
		{
			WM.moveObject(this, battleCity::Vector(position.x + -1, position.y));
		}
		if (change == 3)
		{
			WM.moveObject(this, battleCity::Vector(position.x, position.y + 1));
		}
		if (change == 4)
		{
			WM.moveObject(this, battleCity::Vector(position.x, position.y - 1));
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