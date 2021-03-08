#include "Tank.h"

Tank::Tank()
{
	id = 2;
	type = "Tank";
	speed = 1;
}

Tank::Tank(int x, int y)
{
	position.x = x;
	position.y = y;
	id = 2;
	type = "Tank";
	speed = 1;
}

inline void Tank::update()
{
}

inline void Tank::draw()
{
	drawSprite(sprite[0], (int)position.x, (int)position.y);
}

int Tank::eventHandler(const battleCity::Event* p_event)
{
	return 0;
}

Tank::~Tank()
{
#if DEBUG == 2
	std::cout << "Tank Destructor" << std::endl;
#endif
}