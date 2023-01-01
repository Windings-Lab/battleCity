#pragma once

#include "ObjectFactory.h"

namespace BattleCity::Object
{
	struct BasicObjectFactory : ObjectFactory
	{
		using ObjectFactory::ObjectFactory;

		Object* CreateWorldBoundaries() override;

		Object* CreateTank(Type tankType) override;

		Object* CreateBullet() override;

		Object* CreatePowerUp() override;

		Object* CreateWall() override;

		Object* CreatePhoenix() override;

		Object* CreateExplosion() override;
	};
}
