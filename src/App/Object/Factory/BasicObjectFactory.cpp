#include "PCHeader.h"
#include "BasicObjectFactory.h"

#include "WorldMap.h"

#include "Bullet.h"
#include "Explosion.h"
#include "Phoenix.h"
#include "PowerUp.h"
#include "Tank.h"
#include "Wall.h"
#include "WorldBoundaries.h"

namespace BattleCity::Object
{
	Object* BasicObjectFactory::CreateWorldBoundaries()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Background)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::Basic);

		auto object = std::make_unique<WorldBoundaries>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object), Sprite::Layer::Back);
	}

	Object* BasicObjectFactory::CreateTank(Type tankType)
	{
		switch (tankType)
		{
		case Type::TankNPC:
			mSpriteBuilder.BuildPathGroupAt(R"(.\data\Tank\TankNPC)");
			break;
		case Type::TankPlayer:
			mSpriteBuilder.BuildPathGroupAt(R"(.\data\Tank\TankPlayer)");
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::Up);

		auto object = std::make_unique<Tank>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}

	Object* BasicObjectFactory::CreateBullet()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Bullet)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::Up);

		auto object = std::make_unique<Bullet>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}

	Object* BasicObjectFactory::CreatePowerUp()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\PowerUp)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::Basic);

		auto object = std::make_unique<PowerUp>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object), Sprite::Layer::Front);
	}

	Object* BasicObjectFactory::CreateWall()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Wall)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::Basic);

		auto object = std::make_unique<Wall>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}
	Object* BasicObjectFactory::CreatePhoenix()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\PhoenixAndFlag)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::Phoenix);

		auto object = std::make_unique<Phoenix>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}

	Object* BasicObjectFactory::CreateExplosion()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Explosion)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Sprite::TextureType::ExplosionSmall1);

		auto object = std::make_unique<Explosion>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}
}

