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
	WorldBoundaries* Standart::CreateWorldBoundaries()
	{
		auto object = std::make_unique<WorldBoundaries>(mTextureGroups.GetGroupBy(Framework::TextureName::Background));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		return dynamic_cast<WorldBoundaries*>(mInserter.InsertObject(std::move(object), Layer::Back));
	}

	Tank* Standart::CreateTank(Type tankType)
	{
		std::unique_ptr<Object> object;

		auto spawnBullet = [&]
		{
			return CreateBullet();
		};

		switch (tankType)
		{
		case Type::TankNPC:
			object = std::make_unique<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC), spawnBullet);
			object->ChangeTextureTo(Framework::TextureType::Up);
			break;
		case Type::TankPlayer:
			object = std::make_unique<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankPlayer), spawnBullet);
			object->ChangeTextureTo(Framework::TextureType::Up);
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}

		return dynamic_cast<Tank*>(mInserter.InsertObject(std::move(object)));
	}

	Bullet* Standart::CreateBullet()
	{
		auto object = std::make_unique<Bullet>(mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));
		object->ChangeTextureTo(Framework::TextureType::Up);

		return dynamic_cast<Bullet*>(mInserter.InsertObject(std::move(object)));
	}

	PowerUp* Standart::CreatePowerUp()
	{
		auto object = std::make_unique<PowerUp>(mTextureGroups.GetGroupBy(Framework::TextureName::PowerUp));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		return dynamic_cast<PowerUp*>(mInserter.InsertObject(std::move(object)));
	}

	Wall* Standart::CreateWall()
	{
		auto object = std::make_unique<Wall>(mTextureGroups.GetGroupBy(Framework::TextureName::Wall));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		return dynamic_cast<Wall*>(mInserter.InsertObject(std::move(object)));
	}

	Phoenix* Standart::CreatePhoenix()
	{
		auto object = std::make_unique<Phoenix>(mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));
		object->ChangeTextureTo(Framework::TextureType::Phoenix);

		return dynamic_cast<Phoenix*>(mInserter.InsertObject(std::move(object)));
	}

	Explosion* Standart::CreateExplosion()
	{
		auto object = std::make_unique<Explosion>(mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));
		object->ChangeTextureTo(Framework::TextureType::ExplosionSmall1);

		return dynamic_cast<Explosion*>(mInserter.InsertObject(std::move(object)));
	}
}

