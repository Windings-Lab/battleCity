#include "Wall.h"
#include "Sprites.h"

battleCity::Wall::Wall() : Object(0)
{
	id = 4;
	type = "Wall";

	health = 2;
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

	health = 2;
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
