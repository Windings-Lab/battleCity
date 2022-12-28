#include "PCHeader.h"
#include "BasicObjectFactory.h"

#include "Bullet.h"
#include "Explosion.h"
#include "WorldManager.h"

#include "Object.h"
#include "Phoenix.h"
#include "Tank.h"
#include "Wall.h"
#include "WorldBoundaries.h"


namespace BattleCity::Object
{
	BasicObjectFactory& BasicObjectFactory::GetInstance()
	{
		static BasicObjectFactory objectFactory;
		return objectFactory;
	}

	Object* const BasicObjectFactory::CreateWorldBoundaries()
	{
		auto worldBoundaries = std::make_unique<WorldBoundaries>();
		worldBoundaries->SetSprite({ Sprite::Type::Background, Sprite::Behaviour::Basic });

		auto worldBoundariesPtr = worldBoundaries.get();
		Manager::WM().InsertObject(std::move(worldBoundaries), Sprite::Layer::Back);

		return worldBoundariesPtr;
	}

	Object* const BasicObjectFactory::CreateTank(Type tankType)
	{
		std::unique_ptr<Object> tank;

		switch (tankType)
		{
		case Type::TankNPC:
			tank = std::make_unique<Tank>();
			tank->SetSprite({ Sprite::Type::TankNPC, Sprite::Behaviour::Up });
			break;
		case Type::TankPlayer:
			tank = std::make_unique<Tank>();
			tank->SetSprite({ Sprite::Type::TankPlayer, Sprite::Behaviour::Up });
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}
		
		auto tankPtr = tank.get();
		Manager::WM().InsertObject(std::move(tank), Sprite::Layer::Front);

		return tankPtr;
	}

	Object* const BasicObjectFactory::CreateBullet()
	{
		auto bullet = std::make_unique<Bullet>();
		bullet->SetSprite({ Sprite::Type::Bullet, Sprite::Behaviour::Up });

		auto bulletPtr = bullet.get();
		Manager::WM().InsertObject(std::move(bullet), Sprite::Layer::Front);

		return bulletPtr;
	}

	Object* const BasicObjectFactory::CreatePowerUp()
	{
		auto powerUp = std::make_unique<Tank>();
		powerUp->SetSprite({ Sprite::Type::PowerUp, Sprite::Behaviour::Basic });

		auto powerUpPtr = powerUp.get();
		Manager::WM().InsertObject(std::move(powerUp), Sprite::Layer::Front);

		return powerUpPtr;
	}

	Object* const BasicObjectFactory::CreateWall()
	{
		auto wall = std::make_unique<Wall>();
		wall->SetSprite({ Sprite::Type::Wall, Sprite::Behaviour::Basic });

		auto wallPtr = wall.get();
		Manager::WM().InsertObject(std::move(wall), Sprite::Layer::Front);

		return wallPtr;
	}
	Object* const BasicObjectFactory::CreatePhoenix()
	{
		auto phoenix = std::make_unique<Phoenix>();
		phoenix->SetSprite({ Sprite::Type::Phoenix, Sprite::Behaviour::Basic });

		auto phoenixPtr = phoenix.get();
		Manager::WM().InsertObject(std::move(phoenix), Sprite::Layer::Front);

		return phoenixPtr;
	}

	Object* const BasicObjectFactory::CreateExplosion()
	{
		auto explosion = std::make_unique<Explosion>();
		explosion->SetSprite({ Sprite::Type::Explosion, Sprite::Behaviour::ExplosionSmall1 });

		auto explosionPtr = explosion.get();
		Manager::WM().InsertObject(std::move(explosion), Sprite::Layer::Front);

		return explosionPtr;
	}
}

