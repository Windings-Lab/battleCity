#pragma once

#include "ObjectFactory.h"

namespace BattleCity::Game::World::Object::Factory
{
	struct Standart : Factory
	{
		using Factory::Factory;

		std::shared_ptr<WorldBoundaries> CreateWorldBoundaries() override;

		std::shared_ptr<Tank> CreateTank(Type tankType) override;

		std::shared_ptr<Bullet> CreateBullet() override;

		std::shared_ptr<PowerUp> CreatePowerUp() override;

		std::shared_ptr<Wall> CreateWall() override;

		std::shared_ptr<Phoenix> CreatePhoenix() override;

		std::shared_ptr<Explosion> CreateExplosion() override;
	};
}
