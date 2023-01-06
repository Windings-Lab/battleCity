#include "PCHeader.h"
#include "ObjectFactoryStandart.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroupLibrary.h"
#include "BattleCity/Game/World/WorldMap.h"

#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Derived/Explosion.h"
#include "BattleCity/Game/World/Object/Derived/Phoenix.h"
#include "BattleCity/Game/World/Object/Derived/PowerUp.h"
#include "BattleCity/Game/World/Object/Derived/Tank.h"
#include "BattleCity/Game/World/Object/Derived/Wall.h"
#include "BattleCity/Game/World/Object/Derived/WorldBoundaries.h"

namespace BattleCity::Game::World::Object::Factory
{
	std::shared_ptr<WorldBoundaries> Standart::CreateWorldBoundaries()
	{
		auto object = std::make_shared<WorldBoundaries>(mTextureGroups.GetGroupBy(Framework::TextureName::Background));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		mInserter.InsertObject(object, Layer::Back);

		return object;
	}

	std::shared_ptr<Tank> Standart::CreateTank(Type tankType)
	{
		std::shared_ptr<Tank> object;

		auto spawnBullet = [&]
		{
			return CreateBullet();
		};

		switch (tankType)
		{
		case Type::TankNPC:
			object = std::make_shared<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC), spawnBullet);
			object->ChangeTextureTo(Framework::TextureType::Up);
			break;
		case Type::TankPlayer:
			object = std::make_shared<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankPlayer), spawnBullet);
			object->ChangeTextureTo(Framework::TextureType::Up);
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Bullet> Standart::CreateBullet()
	{
		auto object = std::make_shared<Bullet>(mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));
		object->ChangeTextureTo(Framework::TextureType::Up);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<PowerUp> Standart::CreatePowerUp()
	{
		auto object = std::make_shared<PowerUp>(mTextureGroups.GetGroupBy(Framework::TextureName::PowerUp));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Wall> Standart::CreateWall()
	{
		auto object = std::make_shared<Wall>(mTextureGroups.GetGroupBy(Framework::TextureName::Wall));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Phoenix> Standart::CreatePhoenix()
	{
		auto object = std::make_shared<Phoenix>(mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));
		object->ChangeTextureTo(Framework::TextureType::Phoenix);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Explosion> Standart::CreateExplosion()
	{
		auto object = std::make_shared<Explosion>(mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));
		object->ChangeTextureTo(Framework::TextureType::ExplosionSmall1);

		mInserter.InsertObject(object);

		return object;
	}
}

