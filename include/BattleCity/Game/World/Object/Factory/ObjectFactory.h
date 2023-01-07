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
	class Object;
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

		virtual std::shared_ptr<Object> CreateWorldBoundaries() = 0;

		virtual std::shared_ptr<Object> CreateTank(Type tankType) = 0;

		virtual std::shared_ptr<Object> CreateBullet() = 0;

		virtual std::shared_ptr<Object> CreatePowerUp() = 0;

		virtual std::shared_ptr<Object> CreateWall() = 0;

		virtual std::shared_ptr<Object> CreatePhoenix() = 0;

		virtual std::shared_ptr<Object> CreateExplosion() = 0;

	protected:
		Map& mInserter;
		const Engine::Texture::GroupLibrary& mTextureGroups;
	};
}


