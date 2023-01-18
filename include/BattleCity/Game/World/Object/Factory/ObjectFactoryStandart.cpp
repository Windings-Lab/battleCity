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
#include "BattleCity/Game/World/Object/Containers/QuadTree.h"

namespace BattleCity::Game::World::Object::Factory
{
	std::shared_ptr<WorldBoundaries> Standart::CreateWorldBoundaries(Position position)
	{
		auto object = std::make_shared<WorldBoundaries>(mTextureGroups.GetGroupBy(Framework::TextureName::Background));

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->ChangeTextureTo(Framework::TextureType::Basic);
		object->UpdateCollider();

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
			break;
		case Type::TankPlayer:
			object = std::make_shared<Tank>(mTextureGroups.GetGroupBy(Framework::TextureName::TankPlayer));
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->ChangeTextureTo(Framework::TextureType::Up);
		object->UpdateCollider();

		object->SetBullet(bulletSpawner);
		object->SetSpeed(5);

		mInserter.InsertObject(object);

		object->RegisterObserver(&mQuadTree);
		mQuadTree.Insert(object.get());

		return object;
	}

	std::shared_ptr<Bullet> Standart::CreateBullet(Position position)
	{
		auto object = std::make_shared<Bullet>(mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->UpdateCollider();

		mInserter.InsertObject(object);

		object->RegisterObserver(&mQuadTree);
		mQuadTree.Insert(object.get());

		return object;
	}

	std::shared_ptr<PowerUp> Standart::CreatePowerUp(Position position)
	{
		auto object = std::make_shared<PowerUp>(mTextureGroups.GetGroupBy(Framework::TextureName::PowerUp));

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->ChangeTextureTo(Framework::TextureType::Basic);
		object->UpdateCollider();

		mInserter.InsertObject(object);

		object->RegisterObserver(&mQuadTree);
		mQuadTree.Insert(object.get());

		return object;
	}

	std::shared_ptr<Wall> Standart::CreateWall(Position position)
	{
		auto object = std::make_shared<Wall>(mTextureGroups.GetGroupBy(Framework::TextureName::Wall));

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->ChangeTextureTo(Framework::TextureType::Basic);
		object->UpdateCollider();

		mInserter.InsertObject(object);

		object->RegisterObserver(&mQuadTree);
		mQuadTree.Insert(object.get());

		return object;
	}

	std::shared_ptr<Phoenix> Standart::CreatePhoenix(Position position)
	{
		auto object = std::make_shared<Phoenix>(mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->ChangeTextureTo(Framework::TextureType::Phoenix);
		object->UpdateCollider();

		mInserter.InsertObject(object);

		object->RegisterObserver(&mQuadTree);
		mQuadTree.Insert(object.get());

		return object;
	}

	std::shared_ptr<Explosion> Standart::CreateExplosion(Position position)
	{
		auto object = std::make_shared<Explosion>(mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));

		auto& componentFactory = dynamic_cast<ComponentFactory&>(*object);
		componentFactory.InitializeComponents();

		object->SetPosition(position);
		object->ChangeTextureTo(Framework::TextureType::ExplosionSmall1);

		mInserter.InsertObject(object);

		return object;
	}
}

