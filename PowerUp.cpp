#include "PowerUp.h"
#include "EventCollision.h"
#include "Utility.h"
#include "WorldManager.h"
#include "GameManager.h"

battleCity::PowerUp::PowerUp()
{
	mType = Type::PowerUp;

	int rnd = randomNumber(0, WM.GetPowerUpPositions().size() - 1);
	indexX = WM.GetPowerUpPositions()[rnd][0];
	indexY = WM.GetPowerUpPositions()[rnd][1];
	initPosition(Vector(indexX, indexY));

	mHealth = 1;
	mConstSpeed = 0;
	mBulletCount = 0;
	mSolidness = Solidness::Soft;

	spriteDB = &SPR.getPowerUpSprites();
	SpriteSet(nullptr, 0);
}

battleCity::PowerUp::PowerUp(int giveHealth)
{
	mType = Type::PowerUp;

	int rnd = randomNumber(0, WM.GetPowerUpPositions().size() - 1);
	indexX = WM.GetPowerUpPositions()[rnd][0];
	indexY = WM.GetPowerUpPositions()[rnd][1];
	initPosition(Vector(indexX, indexY));

	mHealth = giveHealth;
	mConstSpeed = 0;
	mBulletCount = 0;
	mSolidness = Solidness::Soft;

	spriteDB = &SPR.getPowerUpSprites();
	SpriteSet(nullptr, 0);
}

void battleCity::PowerUp::Draw()
{
	drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
}

void battleCity::PowerUp::makePowerUp(EventCollision& collisionEvent)
{
	auto& collisionObj = collisionEvent.GetObjectRef();
	if	(collisionObj.GetType() == Type::TankPlayer)
	{
		collisionObj.SetHealth(mHealth);
		WM.MarkForDelete(mID);
		WM.SetPowerUpisTakedToTrue();
	}
}

int battleCity::PowerUp::EventHandler(Event& event)
{
	if (event.GetType() == EventType::Collision)
	{
		makePowerUp(dynamic_cast<EventCollision&>(event));
		return 1;
	}

	return 0;
}

battleCity::PowerUp::~PowerUp()
{
	if (GM.GetGameOver()) return; // TODO: Fix
	WM.SetPowerUpToFalse();
}