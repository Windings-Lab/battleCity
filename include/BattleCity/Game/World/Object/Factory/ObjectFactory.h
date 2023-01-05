#pragma once

namespace BattleCity::Game::World
{
	class Map;
}

namespace BattleCity::Game::World::Object
{
	class Object;
}

namespace BattleCity::Game::World::Object::Factory
{
	struct Factory
	{
		explicit Factory(World::Map& inserter) : mInserter(inserter) {}

		DISALLOW_COPY_MOVE(Factory)

		virtual ~Factory() = default;

		virtual Object* CreateWorldBoundaries() = 0;

		virtual Object* CreateTank(Type tankType) = 0;

		virtual Object* CreateBullet() = 0;

		virtual Object* CreatePowerUp() = 0;

		virtual Object* CreateWall() = 0;

		virtual Object* CreatePhoenix() = 0;

		virtual Object* CreateExplosion() = 0;

	protected:
		World::Map& mInserter;
	};
}


