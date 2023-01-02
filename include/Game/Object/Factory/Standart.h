#pragma once

#include "Factory.h"

namespace BattleCity::Object::Factory
{
	struct Standart : Factory
	{
		using Factory::Factory;

		Object* CreateWorldBoundaries() override;

		Object* CreateTank(Type tankType) override;

		Object* CreateBullet() override;

		Object* CreatePowerUp() override;

		Object* CreateWall() override;

		Object* CreatePhoenix() override;

		Object* CreateExplosion() override;
	};
}
