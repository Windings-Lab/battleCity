#include "PCHeader.h"
#include "Standart.h"

#include "Game/World/Map.h"

#include "Game/Object/Derived/Bullet.h"
#include "Game/Object/Derived/Explosion.h"
#include "Game/Object/Derived/Phoenix.h"
#include "Game/Object/Derived/PowerUp.h"
#include "Game/Object/Derived/Tank.h"
#include "Game/Object/Derived/Wall.h"
#include "Game/Object/Derived/WorldBoundaries.h"

namespace BattleCity::Game::Object::Factory
{
	Object* Standart::CreateWorldBoundaries()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Background)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Texture::Type::Basic);

		auto object = std::make_unique<WorldBoundaries>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object), Sprite::Layer::Back);
	}

	Object* Standart::CreateTank(Type tankType)
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
		mSpriteBuilder.BuildSpriteWith(Texture::Type::Up);

		auto object = std::make_unique<Tank>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}

	Object* Standart::CreateBullet()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Bullet)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Texture::Type::Up);

		auto object = std::make_unique<Bullet>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}

	Object* Standart::CreatePowerUp()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\PowerUp)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Texture::Type::Basic);

		auto object = std::make_unique<PowerUp>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object), Sprite::Layer::Front);
	}

	Object* Standart::CreateWall()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Wall)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Texture::Type::Basic);

		auto object = std::make_unique<Wall>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}
	Object* Standart::CreatePhoenix()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\PhoenixAndFlag)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Texture::Type::Phoenix);

		auto object = std::make_unique<Phoenix>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}

	Object* Standart::CreateExplosion()
	{
		mSpriteBuilder.BuildPathGroupAt(R"(.\data\Explosion)");
		mSpriteBuilder.BuildTextures();
		mSpriteBuilder.BuildSpriteWith(Texture::Type::ExplosionSmall1);

		auto object = std::make_unique<Explosion>(mSpriteBuilder.GetSprite());

		return mInserter.InsertObject(std::move(object));
	}
}

