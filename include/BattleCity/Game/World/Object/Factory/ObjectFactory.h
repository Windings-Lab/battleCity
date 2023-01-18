#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Engine::Texture
{
	class GroupLibrary;
}

namespace BattleCity::Game::World
{
	class Map;
}

namespace BattleCity::Game::World::Object
{
	class QuadTree;

	class Explosion;
	class Phoenix;
	class Wall;
	class PowerUp;
	class Bullet;
	class Tank;
	class WorldBoundaries;
	class Object;
}

namespace BattleCity::Game::World::Object::Factory
{
	struct Factory
	{
		explicit Factory(Map&, const Engine::Texture::GroupLibrary&, QuadTree&);

		DISALLOW_COPY_MOVE(Factory)

		virtual ~Factory() = default;

		virtual std::shared_ptr<WorldBoundaries> CreateWorldBoundaries(Position = {0, 0}) = 0;

		virtual std::shared_ptr<Tank> CreateTank(Type tankType, Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Bullet> CreateBullet(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<PowerUp> CreatePowerUp(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Wall> CreateWall(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Phoenix> CreatePhoenix(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Explosion> CreateExplosion(Position = { 0, 0 }) = 0;

	protected:
		Map& mInserter;
		const Engine::Texture::GroupLibrary& mTextureGroups;

		QuadTree& mQuadTree;
	};
}


