#include "PCHeader.h"
#include "ObjectFactoryStandart.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroupLibrary.h"

#include "BattleCity/Game/World/Object/Derived/Background.h"
#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Derived/Explosion.h"
#include "BattleCity/Game/World/Object/Derived/Phoenix.h"
#include "BattleCity/Game/World/Object/Derived/PowerUp.h"
#include "BattleCity/Game/World/Object/Derived/Tank.h"
#include "BattleCity/Game/World/Object/Derived/Wall.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object::Factory
{
	std::shared_ptr<Background> Standart::CreateWorldBoundaries(Position position)
	{
		auto object = std::make_shared<Background>();
		object->SetDestroyMarker(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Background));
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		object->SetPosition(position);

		mInsertToMap(object, Layer::Back);

		return object;
	}

	std::shared_ptr<Tank> Standart::CreateTank(Type tankType, Position position)
	{
		auto object = std::make_shared<Tank>();
		object->SetDestroyMarker(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();

		switch (tankType)
		{
		case Type::TankNPC:
			textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC));
			break;
		case Type::TankPlayer:
			textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::TankPlayer));
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}

		auto movable = object->GetComponent<Component::Movable>();
		movable->SetSpeed(5);
		movable->SetDirection(Direction::Up);
		movable->StopMovement();

		object->SetPosition(position);

		auto fireable = object->GetComponent<Component::Fireable>();
		fireable->SetBullet(*this);
		fireable->SetBulletCount(1);

		mInsertToMap(object, Layer::Front);

		object->GetComponent<Component::Collider>()->UpdateCollider();
		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Bullet> Standart::CreateBullet(Position position, Direction direction)
	{
		auto object = std::make_shared<Bullet>();
		object->SetDestroyMarker(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));

		auto movable = object->GetComponent<Component::Movable>();
		movable->SetSpeed(1);
		movable->SetDirection(direction);

		object->SetPosition(position);
		object->AdjustPositionToDirection();

		mInsertToMap(object, Layer::Front);

		object->GetComponent<Component::Collider>()->UpdateCollider();
		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<PowerUp> Standart::CreatePowerUp(Position position)
	{
		/*auto object = std::make_shared<PowerUp>();
		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::PowerUp));

		object->SetPosition(position);
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		mInserter.InsertObject(object);

		object->RegisterObserver(&mQuadTree);
		mQuadTree.Insert(object.get());*/

		return nullptr;
	}

	std::shared_ptr<Wall> Standart::CreateWall(Position position)
	{
		auto object = std::make_shared<Wall>();
		object->SetDestroyMarker(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Wall));

		object->SetPosition(position);
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		object->GetComponent<Component::Health>()->SetHealth(1);

		mInsertToMap(object, Layer::Front);

		object->GetComponent<Component::Collider>()->UpdateCollider();
		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Phoenix> Standart::CreatePhoenix(Position position)
	{
		auto object = std::make_shared<Phoenix>();
		object->SetDestroyMarker(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));

		object->SetPosition(position);
		textureComponent->ChangeTextureTo(Framework::TextureType::Phoenix);

		mInsertToMap(object, Layer::Front);

		object->GetComponent<Component::Collider>()->UpdateCollider();
		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Explosion> Standart::CreateExplosion(Position position)
	{
		auto object = std::make_shared<Explosion>();
		object->SetDestroyMarker(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));

		object->SetPosition(position);
		textureComponent->ChangeTextureTo(Framework::TextureType::ExplosionSmall1);

		mInsertToMap(object, Layer::Front);

		return object;
	}
}

