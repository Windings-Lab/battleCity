#include "Wall.h"
#include "Sprites.h"

#include <iostream>

battleCity::Wall::Wall() : Object(0)
{
	id = 4;
	type = "Wall";

#if DEBUG == 0
	health = 2;
#else
	health = 10;
#endif
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::HARD;

	spriteSet(&SPR.getWallSprite());
}

battleCity::Wall::Wall(float x, float y) : Object(0)
{
	id = 4;
	type = "Wall";

	position.x = x;
	position.y = y;

#if DEBUG == 0
	health = 2;
#else
	health = 10;
#endif
	constSpeed = 0;
	bulletCount = 0;
	solidness = Solidness::HARD;

	spriteSet(&SPR.getWallSprite());
}

void battleCity::Wall::update()
{
}

void battleCity::Wall::draw()
{
	drawSprite(sprite, (int)position.x, (int)position.y);
}

int battleCity::Wall::eventHandler(const Event* ptrEvent)
{
	return 0;
}

battleCity::Wall::~Wall()
{
#if DEBUG == 2
	std::cout << "Wall Destructor" << std::endl;
#endif
}