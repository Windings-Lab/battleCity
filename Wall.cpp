#include "Wall.h"
#include "Sprites.h"

namespace battleCity
{
	Wall::Wall() : Object()
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

	Wall::Wall(float x, float y) : Object()
	{
		mType = Type::Wall;

		position.X = x;
		position.Y = y;

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
		drawSprite(sprite, (int)position.X, (int)position.Y);
	}

	int Wall::eventHandler(const Event* ptrEvent)
	{
		return 0;
	}

	Wall::~Wall()
	{

	}
}