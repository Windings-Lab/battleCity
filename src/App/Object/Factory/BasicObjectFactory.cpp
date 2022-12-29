#include "PCHeader.h"
#include "BasicObjectFactory.h"

#include "Bullet.h"
#include "Explosion.h"
#include "WorldMap.h"

#include "Object.h"
#include "Phoenix.h"
#include "PowerUp.h"
#include "Tank.h"
#include "Wall.h"
#include "WorldBoundaries.h"

namespace BattleCity::Object
{
	Object* const BasicObjectFactory::CreateWorldBoundaries()
	{
		auto worldBoundaries = std::make_unique<WorldBoundaries>();
		worldBoundaries->CreateSprite(R"(.\data\Background)");
		worldBoundaries->SetSprite(Sprite::Type::Basic);

		auto worldBoundariesPtr = worldBoundaries.get();
		mInserter.InsertObject(std::move(worldBoundaries), Sprite::Layer::Back);

		return worldBoundariesPtr;
	}

	Object* const BasicObjectFactory::CreateTank(Type tankType)
	{
		std::unique_ptr<Object> tank;

		switch (tankType)
		{
		case Type::TankNPC:
			tank = std::make_unique<Tank>();
			tank->CreateSprite(R"(.\data\Tank\TankNPC)");
			tank->SetSprite(Sprite::Type::Up);
			break;
		case Type::TankPlayer:
			tank = std::make_unique<Tank>();
			tank->CreateSprite(R"(.\data\Tank\TankPlayer)");
			tank->SetSprite(Sprite::Type::Up);
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}
		
		auto tankPtr = tank.get();
		mInserter.InsertObject(std::move(tank), Sprite::Layer::Front);

		return tankPtr;
	}

	Object* const BasicObjectFactory::CreateBullet()
	{
		auto bullet = std::make_unique<Bullet>();
		bullet->CreateSprite(R"(.\data\Bullet)");
		bullet->SetSprite(Sprite::Type::Up);

		auto bulletPtr = bullet.get();
		mInserter.InsertObject(std::move(bullet), Sprite::Layer::Front);

		return bulletPtr;
	}

	Object* const BasicObjectFactory::CreatePowerUp()
	{
		auto powerUp = std::make_unique<PowerUp>();
		powerUp->CreateSprite(R"(.\data\PowerUp)");
		powerUp->SetSprite(Sprite::Type::Basic);

		auto powerUpPtr = powerUp.get();
		mInserter.InsertObject(std::move(powerUp), Sprite::Layer::Front);

		return powerUpPtr;
	}

	Object* const BasicObjectFactory::CreateWall()
	{
		auto wall = std::make_unique<Wall>();
		wall->CreateSprite(R"(.\data\Wall)");
		wall->SetSprite(Sprite::Type::Basic);

		auto wallPtr = wall.get();
		mInserter.InsertObject(std::move(wall), Sprite::Layer::Front);

		return wallPtr;
	}
	Object* const BasicObjectFactory::CreatePhoenix()
	{
		auto phoenix = std::make_unique<Phoenix>();
		phoenix->CreateSprite(R"(.\data\PhoenixAndFlag)");
		phoenix->SetSprite(Sprite::Type::Phoenix);

		auto phoenixPtr = phoenix.get();
		mInserter.InsertObject(std::move(phoenix), Sprite::Layer::Front);

		return phoenixPtr;
	}

	Object* const BasicObjectFactory::CreateExplosion()
	{
		auto explosion = std::make_unique<Explosion>();
		explosion->CreateSprite(R"(.\data\Explosion)");
		explosion->SetSprite(Sprite::Type::ExplosionSmall1);

		auto explosionPtr = explosion.get();
		mInserter.InsertObject(std::move(explosion), Sprite::Layer::Front);

		return explosionPtr;
	}
}

