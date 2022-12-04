#include "Tank.h"

#include "Explosion.h"
#include "GameManager.h"
#include "WorldManager.h"

#include <memory>

namespace battleCity
{
	Tank::Tank() : Object(Type::Tank)
	{
	}

	void Tank::Draw()
	{
		// drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}

	void Tank::Fire()
	{
		// if (mBulletCount != 0)
		// {
		// 	std::unique_ptr<Object> bullet = std::make_unique<Bullet>(ObjectType);
		// 	WM.InsertObject(bullet);
		// 	mBulletCount--;
		// }
	}

	void Tank::EventHandler(Event& event)
	{

	}

	Tank::~Tank()
	{
		if(GM.GetGameOver()) return; // TODO: Fix

		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(true);
		newExp->SetPosition(X(), Y());

		WM.InsertObject(newExp);
	}
}
