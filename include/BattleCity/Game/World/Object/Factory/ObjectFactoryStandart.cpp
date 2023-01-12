#include "PCHeader.h"
#include "ObjectFactoryStandart.h"

#include "BattleCity/Game/World/WorldMap.h"

#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Derived/Explosion.h"
#include "BattleCity/Game/World/Object/Derived/Phoenix.h"
#include "BattleCity/Game/World/Object/Derived/PowerUp.h"
#include "BattleCity/Game/World/Object/Derived/Tank.h"
#include "BattleCity/Game/World/Object/Derived/Wall.h"
#include "BattleCity/Game/World/Object/Derived/WorldBoundaries.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroupLibrary.h"

#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object::Factory
{
	std::shared_ptr<WorldBoundaries> Standart::CreateWorldBoundaries(Position position)
	{
		auto object = std::make_shared<WorldBoundaries>(mTextureGroups.GetGroupBy(Framework::TextureName::Background));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object, Layer::Back);

		return object;
	}

	std::shared_ptr<Tank> Standart::CreateTank(Type tankType, Position position)
	{
		std::shared_ptr<Tank> object;

		auto bulletSpawner = [&](Position pos)
		{
			return CreateBullet(pos);
		};

		switch (tankType)
		{
		case Type::TankNPC:
			object = std::make_shared<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC));
			object->ChangeTextureTo(Framework::TextureType::Up);
			break;
		case Type::TankPlayer:
			object = std::make_shared<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankPlayer));
			object->ChangeTextureTo(Framework::TextureType::Up);
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}

		object->AddComponent<Component::Fireable>(bulletSpawner)->SetBulletCount(1);
		object->AddComponent<Component::Movable>()->SetDirection(Framework::TextureType::Up).ResetDirection().SetSpeed(10);
		object->AddComponent<Component::Collider>();

		object->OnComponentInitialization();

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Bullet> Standart::CreateBullet(Position position)
	{
		auto object = std::make_shared<Bullet>(mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));

		object->AddComponent<Component::Movable>()->SetSpeed(20);
		object->AddComponent<Component::Collider>();
		object->OnComponentInitialization();

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<PowerUp> Standart::CreatePowerUp(Position position)
	{
		auto object = std::make_shared<PowerUp>(mTextureGroups.GetGroupBy(Framework::TextureName::PowerUp));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Wall> Standart::CreateWall(Position position)
	{
		auto object = std::make_shared<Wall>(mTextureGroups.GetGroupBy(Framework::TextureName::Wall));
		object->ChangeTextureTo(Framework::TextureType::Basic);

		object->AddComponent<Component::Collider>();
		object->OnComponentInitialization();

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Phoenix> Standart::CreatePhoenix(Position position)
	{
		auto object = std::make_shared<Phoenix>(mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));
		object->ChangeTextureTo(Framework::TextureType::Phoenix);

		object->AddComponent<Component::Collider>();
		object->OnComponentInitialization();

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object);

		return object;
	}

	std::shared_ptr<Explosion> Standart::CreateExplosion(Position position)
	{
		auto object = std::make_shared<Explosion>(mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));
		object->ChangeTextureTo(Framework::TextureType::ExplosionSmall1);

		object->SetPosition(position);
		object->SetDrawPosition(position);

		mInserter.InsertObject(object);

		return object;
	}
}

