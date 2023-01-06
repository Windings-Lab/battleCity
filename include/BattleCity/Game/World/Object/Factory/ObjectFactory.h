#pragma once

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
	class Explosion;
	class Phoenix;
	class PowerUp;
	class Wall;
	class Bullet;
	class Tank;
	class WorldBoundaries;
}

namespace BattleCity::Game::World::Object::Factory
{
	struct Factory
	{
		explicit Factory(Map& inserter, const Engine::Texture::GroupLibrary& textureGroups)
			: mInserter(inserter)
			, mTextureGroups(textureGroups)
		{}

		DISALLOW_COPY_MOVE(Factory)

		virtual ~Factory() = default;

		virtual WorldBoundaries* CreateWorldBoundaries() = 0;

		virtual Tank* CreateTank(Type tankType) = 0;

		virtual Bullet* CreateBullet() = 0;

		virtual PowerUp* CreatePowerUp() = 0;

		virtual Wall* CreateWall() = 0;

		virtual Phoenix* CreatePhoenix() = 0;

		virtual Explosion* CreateExplosion() = 0;

	protected:
		Map& mInserter;
		const Engine::Texture::GroupLibrary& mTextureGroups;
	};
}


