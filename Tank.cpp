#include "Tank.h"

Tank::Tank()
{
	position.x = 400;
	position.y = 300;
	id = 2;
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