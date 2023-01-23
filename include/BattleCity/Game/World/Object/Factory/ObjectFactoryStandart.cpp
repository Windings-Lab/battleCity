#include "PCHeader.h"
#include "ObjectFactoryStandart.h"

#include "BattleCity/Engine/Texture/BCTexture.h"
#include "BattleCity/Engine/Texture/TextureGroupLibrary.h"

#include "BattleCity/Game/World/Object/Derived/Background.h"
#include "BattleCity/Game/World/Object/Derived/Bullet.h"
#include "BattleCity/Game/World/Object/Derived/Explosion.h"
#include "BattleCity/Game/World/Object/Derived/Phoenix.h"
#include "BattleCity/Game/World/Object/Derived/PowerUp.h"
#include "BattleCity/Game/World/Object/Derived/Tank/Tank.h"
#include "BattleCity/Game/World/Object/Derived/Tank/TankNPC.h"
#include "BattleCity/Game/World/Object/Derived/Wall.h"
#include "BattleCity/Game/World/Object/Derived/GameOver.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Explodable.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object::Factory
{
	std::shared_ptr<Background> Standart::CreateBackgrounds(Position position)
	{
		auto object = std::make_shared<Background>();
		object->SetDestroyMarkerFunc(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Background));
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		object->SetPosition(position);

		mInsertToMap(object, Layer::Back);

		return object;
	}

	std::shared_ptr<GameOver> Standart::CreateGameOver(Position)
	{
		auto object = std::make_shared<GameOver>();

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::GameOver));
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		auto screenCenter = mScreenBounds.GetCenter();
		object->SetPosition({ screenCenter.X - textureComponent->GetSize().X / 2
								, mScreenBounds.GetHeight() });

		object->SetEndAnimationPosition(screenCenter);

		auto collider = object->GetComponent<Component::Collider>();
		collider->UpdateCollider();
		collider->SetSolid(false);

		mInsertToMap(object, Layer::UI);

		return object;
	}

	std::shared_ptr<Tank> Standart::CreateTank(Type tankType, Position position)
	{
		std::shared_ptr<Tank> object;

		Component::Texture* textureComponent;
		Component::Movable* movable;

		switch (tankType)
		{
		case Type::TankNPC:
			object = std::make_shared<TankNPC>();
			movable = object->GetComponent<Component::Movable>();
			textureComponent = object->GetComponent<Component::Texture>();
			textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC));
			movable->SetSpeed(3);
			movable->SetMovementDirection(Direction::Down);
			break;
		case Type::TankPlayer:
			object = std::make_shared<Tank>();
			movable = object->GetComponent<Component::Movable>();
			textureComponent = object->GetComponent<Component::Texture>();
			textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::TankPlayer));
			movable->SetSpeed(3);
			movable->SetMovementDirection(Direction::Up);
			movable->StopMovement();
			break;
		default:
			std::cerr << "Incorrect tank type\n";
			return nullptr;
		}
		object->SetDestroyMarkerFunc(mObjectDestroyer);

		object->SetPosition(position);

		auto fireable = object->GetComponent<Component::Fireable>();
		fireable->SetBullet(*this);
		fireable->SetBulletCount(1);

		mInsertToMap(object, Layer::Middle);

		auto collider = object->GetComponent<Component::Collider>();
		collider->UpdateCollider();
		collider->SetSolid(true);

		auto explodable = object->GetComponent<Component::Explodable>();
		explodable->SetExplosionSpawner(*this);

		object->GetComponent<Component::Health>()->SetHealth(1);

		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Bullet> Standart::CreateBullet(Position position, Direction direction)
	{
		auto object = std::make_shared<Bullet>();
		object->SetDestroyMarkerFunc(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));

		auto movable = object->GetComponent<Component::Movable>();
		movable->SetSpeed(5);
		movable->SetMovementDirection(direction);

		object->SetPosition(position);
		object->AdjustPositionToDirection();

		auto collider = object->GetComponent<Component::Collider>();
		collider->UpdateCollider();
		collider->SetSolid(false);
		if (collider->GetRectangle().OutOfInner(mWorldBounds))
		{
			object.reset();
			return nullptr;
		}

		auto explodable = object->GetComponent<Component::Explodable>();
		explodable->SetExplosionSpawner(*this);

		mInsertToMap(object, Layer::Middle);

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
		object->SetDestroyMarkerFunc(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Wall));

		object->SetPosition(position);
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		object->GetComponent<Component::Health>()->SetHealth(1);

		mInsertToMap(object, Layer::Middle);

		auto collider = object->GetComponent<Component::Collider>();
		collider->UpdateCollider();
		collider->SetSolid(true);
		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Phoenix> Standart::CreatePhoenix(Position position)
	{
		auto object = std::make_shared<Phoenix>();
		object->SetDestroyMarkerFunc(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));

		object->SetPosition(position);
		textureComponent->ChangeTextureTo(Framework::TextureType::Phoenix);

		auto explodable = object->GetComponent<Component::Explodable>();
		explodable->SetExplosionSpawner(*this);

		object->GetComponent<Component::Health>()->SetHealth(1);

		mInsertToMap(object, Layer::Middle);

		auto collider = object->GetComponent<Component::Collider>();
		collider->UpdateCollider();
		collider->SetSolid(true);
		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Explosion> Standart::CreateExplosion(ExplosionType type, Position position)
	{
		auto object = std::make_shared<Explosion>();
		object->SetDestroyMarkerFunc(mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));

		switch (type)
		{
		case ExplosionType::Large:
			textureComponent->ChangeTextureTo(Framework::TextureType::ExplosionLarge1);
			break;
		case ExplosionType::Small:
			textureComponent->ChangeTextureTo(Framework::TextureType::ExplosionSmall1);
			break;
		case ExplosionType::Error:
		default:
			{
			assert(false && "CreateExplosion: Invalid explosion type");
			return nullptr;
			}
		}

		auto textureHalfSize = textureComponent->GetSize() / 2;
		object->SetPosition(position - textureHalfSize);

		mInsertToMap(object, Layer::Front);

		return object;
	}
}

