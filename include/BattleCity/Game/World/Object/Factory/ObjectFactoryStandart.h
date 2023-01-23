#pragma once

#include "ObjectFactory.h"

namespace BattleCity::Game::World::Object::Factory
{
	struct Standart : Factory
	{
		using Factory::Factory;

		std::shared_ptr<Background> CreateWorldBoundaries(Position = { 0, 0 }) override;

		std::shared_ptr<Tank> CreateTank(Type tankType, Position = { 0, 0 }) override;

		std::shared_ptr<Bullet> CreateBullet(Position, Direction) override;

		std::shared_ptr<PowerUp> CreatePowerUp(Position = { 0, 0 }) override;

		std::shared_ptr<Wall> CreateWall(Position = { 0, 0 }) override;

		std::shared_ptr<Phoenix> CreatePhoenix(Position = { 0, 0 }) override;

		std::shared_ptr<Explosion> CreateExplosion(Position = { 0, 0 }) override;
	};
}
