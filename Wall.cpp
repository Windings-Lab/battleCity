#include "Wall.h"
#include "Sprites.h"

#include <iostream>

namespace battleCity
{
	Wall::Wall() : Object(0)
	{
		mType = Type::Wall;

#if DEBUG == 0
		health = 2;
#else
		health = 10;
#endif
		constSpeed = 0;
		bulletCount = 0;
		solidness = Solidness::Hard;

		spriteSet(&SPR.getWallSprite());
	}

	Wall::Wall(float x, float y) : Object(0)
	{
		mType = Type::Wall;

		position.x = x;
		position.y = y;

#if DEBUG == 0
		health = 2;
#else
		health = 10;
#endif
		constSpeed = 0;
		bulletCount = 0;
		solidness = Solidness::Hard;

		spriteSet(&SPR.getWallSprite());
	}

	void Wall::update()
	{
	}

	void Wall::draw()
	{
		drawSprite(sprite, (int)position.x, (int)position.y);
	}

	int Wall::eventHandler(const Event* ptrEvent)
	{
		return 0;
	}

	Wall::~Wall()
	{
#if DEBUG == 2
		std::cout << "Wall Destructor" << std::endl;
#endif
	}
}