#include "Wall.h"

battleCity::Wall::Wall()
{
	type = "Wall";
	solidness = Solidness::SPECTRAL;
}

void battleCity::Wall::update()
{
}

void battleCity::Wall::draw()
{
}

int battleCity::Wall::eventHandler(const Event* ptrEvent)
{
	return 0;
}
