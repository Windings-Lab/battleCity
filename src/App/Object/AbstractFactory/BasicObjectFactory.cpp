#include "PCHeader.h"
#include "BasicObjectFactory.h"

#include "SpriteData.h"
#include "BCSprite.h"

#include "WorldMap.h"

#include "Object.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Phoenix.h"
#include "PowerUp.h"
#include "Tank.h"
#include "Texture.h"
#include "Wall.h"
#include "WorldBoundaries.h"

namespace BattleCity::Object
{
	Object* BasicObjectFactory::CreateWorldBoundaries(X x, Y y)
	{
		Sprite::SpriteData spriteData;
		spriteData.Init(R"(.\data\Background)");
		Sprite::TextureContainer textureContainer;
		for (const auto& [textureType, texturePath] : spriteData)
		{
			Sprite::Texture texture = Sprite::Texture::Create(texturePath);
			textureContainer.try_emplace(textureType, std::move(texture));
		}

		Sprite::BCSprite sprite(textureContainer);

		auto worldBoundaries = std::make_unique<WorldBoundaries>(sprite, Position(x, y));
		worldBoundaries->ChangeTexture(Sprite::TextureType::Basic);

		auto& worldBoundariesPtr = *worldBoundaries;
		mInserter.InsertObject(std::move(worldBoundaries), Sprite::Layer::Back);

		return &worldBoundariesPtr;
	}

	Object* BasicObjectFactory::CreateTank(Type tankType, X x, Y y)
	{
		std::unique_ptr<Object> tank;

		switch (tankType)
		{
		case Type::TankNPC:
			break;
		case Type::TankPlayer:
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}

		//mInserter.InsertObject(std::move(tank), Sprite::Layer::Front);

		return nullptr;
	}

	Object* BasicObjectFactory::CreateBullet(X x, Y y)
	{
		//mInserter.InsertObject(std::move(bullet), Sprite::Layer::Front);

		return nullptr;
	}

	Object* BasicObjectFactory::CreatePowerUp(X x, Y y)
	{
		//mInserter.InsertObject(std::move(powerUp), Sprite::Layer::Front);

		return nullptr;
	}

	Object* BasicObjectFactory::CreateWall(X x, Y y)
	{
		//mInserter.InsertObject(std::move(wall), Sprite::Layer::Front);

		return nullptr;
	}
	Object* BasicObjectFactory::CreatePhoenix(X x, Y y)
	{
		//mInserter.InsertObject(std::move(phoenix), Sprite::Layer::Front);

		return nullptr;
	}

	Object* BasicObjectFactory::CreateExplosion(X x, Y y)
	{
		//mInserter.InsertObject(std::move(explosion), Sprite::Layer::Front);

		return nullptr;
	}
}

