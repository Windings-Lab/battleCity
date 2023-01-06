#pragma once

#include "ObjectFactory.h"

namespace BattleCity::Game::World::Object::Factory
{
	struct Standart : Factory
	{
		using Factory::Factory;

		WorldBoundaries* CreateWorldBoundaries() override;

		Tank* CreateTank(Type tankType) override;

		Bullet* CreateBullet() override;

		PowerUp* CreatePowerUp() override;

		Wall* CreateWall() override;

		Phoenix* CreatePhoenix() override;

		Explosion* CreateExplosion() override;
	};
}
