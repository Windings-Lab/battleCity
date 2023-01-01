#pragma once

#include "ObjectAbstractFactory.h"

namespace BattleCity::Object
{
	struct BasicObjectFactory : ObjectAbstractFactory
	{
		using ObjectAbstractFactory::ObjectAbstractFactory;

		Object* CreateWorldBoundaries(X = 0, Y = 0) override;

		Object* CreateTank(Type tankType, X = 0, Y = 0) override;

		Object* CreateBullet(X = 0, Y = 0) override;

		Object* CreatePowerUp(X = 0, Y = 0) override;

		Object* CreateWall(X = 0, Y = 0) override;

		Object* CreatePhoenix(X = 0, Y = 0) override;

		Object* CreateExplosion(X = 0, Y = 0) override;
	};
}
