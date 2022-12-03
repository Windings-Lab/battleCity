#include "Wall.h"
#include "Sprites.h"

namespace battleCity
{
	Wall::Wall() : Object()
	{
		mType = Type::Wall;

#if DEBUG == 0
		mHealth = 2;
#else
		health = 10;
#endif
		mConstSpeed = 0;
		mBulletCount = 0;
		mSolidness = Solidness::Hard;

		SetSprite(&SPR.getWallSprite());
	}

	Wall::Wall(float x, float y) : Object()
	{
		mType = Type::Wall;

		mPosition.X = x;
		mPosition.Y = y;

#if DEBUG == 0
		mHealth = 2;
#else
		health = 10;
#endif
		mConstSpeed = 0;
		mBulletCount = 0;
		mSolidness = Solidness::Hard;

		SetSprite(&SPR.getWallSprite());
	}

	void Wall::Update()
	{
	}

	void Wall::Draw()
	{
		drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}

	Wall::~Wall()
	{

	}
}