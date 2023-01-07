#pragma once

#include "ObjectFactory.h"

namespace BattleCity::Game::World::Object::Factory
{
	struct Standart : Factory
	{
		using Factory::Factory;

		std::shared_ptr<Object> CreateWorldBoundaries() override;

		std::shared_ptr<Object> CreateTank(Type tankType) override;

		std::shared_ptr<Object> CreateBullet() override;

		std::shared_ptr<Object> CreatePowerUp() override;

		std::shared_ptr<Object> CreateWall() override;

		std::shared_ptr<Object> CreatePhoenix() override;

		std::shared_ptr<Object> CreateExplosion() override;
	};
}
