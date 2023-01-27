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
#include "BattleCity/Game/World/Object/Derived/Tank/TankSpawnerPoint.h"
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
		auto object = std::make_shared<Background>(position, mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Background));
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		mInsertToMap(object, Layer::Back);

		return object;
	}

	std::shared_ptr<GameOver> Standart::CreateGameOver(Position)
	{
		auto screenCenter = mScreenBounds.GetCenter();

		Vector2Int textureSize;
		mTextureGroups.GetGroupBy(Framework::TextureName::GameOver)
			.GetTextureBy(Framework::TextureType::Basic)
			->GetSize(textureSize.X, textureSize.Y);

		Vector2Int pos = { screenCenter.X - (textureSize.X >> 1), mScreenBounds.GetHeight() };

		auto object = std::make_shared<GameOver>(pos, mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::GameOver));
		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		object->SetEndAnimationPosition(screenCenter);

		auto collider = object->GetComponent<Component::Collider>();
		collider->SetSize(textureComponent->GetSize());
		collider->UpdateCollider();
		collider->SetSolid(false);
		collider->SetColliderType(Type::GameOver);

		mInsertToMap(object, Layer::UI);

		return object;
	}

	std::shared_ptr<Tank> Standart::CreateTank(Type tankType, Position position)
	{
		std::shared_ptr<Tank> object;

		Component::Texture* textureComponent;
		Component::Movable* movable;
		Component::Collider* collider;

		switch (tankType)
		{
		case Type::TankNPC:
			object = std::make_shared<TankNPC>(position, mObjectDestroyer);
			movable = object->GetComponent<Component::Movable>();
			collider = object->GetComponent<Component::Collider>();
			collider->SetColliderType(Type::TankNPC);

			textureComponent = object->GetComponent<Component::Texture>();
			textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC));
			movable->SetSpeed(3);
			movable->SetMovementDirection(Direction::Down);
			break;
		case Type::TankPlayer:
			object = std::make_shared<Tank>(position, mObjectDestroyer);
			movable = object->GetComponent<Component::Movable>();
			collider = object->GetComponent<Component::Collider>();
			collider->SetColliderType(Type::TankPlayer);

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

		auto fireable = object->GetComponent<Component::Fireable>();
		fireable->SetBullet(*this);
		fireable->SetBulletCount(1);

		mInsertToMap(object, Layer::Middle);

		collider->SetSize(textureComponent->GetSize());
		collider->UpdateCollider();
		collider->SetSolid(true);

		auto explodable = object->GetComponent<Component::Explodable>();
		explodable->SetExplosionSpawner(*this);

		object->GetComponent<Component::Health>()->SetHealth(1);

		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Bullet> Standart::CreateBullet(Position position, Direction direction, Type ignoreColliderType)
	{
		auto object = std::make_shared<Bullet>(ignoreColliderType, position, mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Bullet));

		auto movable = object->GetComponent<Component::Movable>();
		movable->SetSpeed(5);
		movable->SetMovementDirection(direction);

		auto collider = object->GetComponent<Component::Collider>();

		auto colliderSize = textureComponent->GetSize();

		switch (direction)
		{
		case Direction::Right:
		case Direction::Left:
			colliderSize.Y *= 5;
			break;
		case Direction::Down:
		case Direction::Up:
			colliderSize.X *= 5;
			break;
		}

		collider->SetSize(colliderSize);
		collider->UpdateCollider();
		object->AdjustPositionToDirection();
		collider->SetSolid(false);
		collider->SetColliderType(Type::Bullet);
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
		auto object = std::make_shared<Wall>(position, mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Wall));

		textureComponent->ChangeTextureTo(Framework::TextureType::Basic);

		object->GetComponent<Component::Health>()->SetHealth(1);

		mInsertToMap(object, Layer::Middle);

		auto collider = object->GetComponent<Component::Collider>();
		collider->SetSize(textureComponent->GetSize());
		collider->UpdateCollider();
		collider->SetSolid(true);
		collider->SetColliderType(Type::Wall);

		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Phoenix> Standart::CreatePhoenix(Position position)
	{
		auto object = std::make_shared<Phoenix>(position, mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Phoenix));

		textureComponent->ChangeTextureTo(Framework::TextureType::Phoenix);

		auto explodable = object->GetComponent<Component::Explodable>();
		explodable->SetExplosionSpawner(*this);

		object->GetComponent<Component::Health>()->SetHealth(1);

		mInsertToMap(object, Layer::Middle);

		auto collider = object->GetComponent<Component::Collider>();
		collider->SetSize(textureComponent->GetSize());
		collider->UpdateCollider();
		collider->SetSolid(true);
		collider->SetColliderType(Type::Phoenix);

		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}

	std::shared_ptr<Explosion> Standart::CreateExplosion(ExplosionType type, Position position)
	{
		Vector2Int textureSize;

		Framework::TextureType textureType;

		switch (type)
		{
		case ExplosionType::Large:
			textureType = Framework::TextureType::ExplosionLarge1;
			break;
		case ExplosionType::Small:
			textureType = Framework::TextureType::ExplosionSmall1;
			break;
		case ExplosionType::Error:
		default:
			assert(false && "CreateExplosion: Invalid explosion type");
			return nullptr;
		}

		mTextureGroups.GetGroupBy(Framework::TextureName::Explosion)
			.GetTextureBy(textureType)
			->GetSize(textureSize.X, textureSize.Y);

		auto textureHalfSize = textureSize / 2;
		auto object = std::make_shared<Explosion>(position - textureHalfSize, mObjectDestroyer);

		auto textureComponent = object->GetComponent<Component::Texture>();
		textureComponent->SetTextureGroup(&mTextureGroups.GetGroupBy(Framework::TextureName::Explosion));
		textureComponent->ChangeTextureTo(textureType);

		mInsertToMap(object, Layer::Front);

		return object;
	}

	std::shared_ptr<TankSpawnerPoint> Standart::CreateTankSpawnPointer(Position position)
	{
		auto object = std::make_shared<TankSpawnerPoint>(position, mObjectDestroyer);

		object->SetTankCreator(*this);

		auto& tankGroup = mTextureGroups.GetGroupBy(Framework::TextureName::TankNPC);
		auto tankTexture = tankGroup.GetTextureBy(Framework::TextureType::Up);

		Size tankTextureSize;
		tankTexture->GetSize(tankTextureSize.X, tankTextureSize.Y);

		auto collider = object->GetComponent<Component::Collider>();
		collider->SetSize(tankTextureSize);
		collider->UpdateCollider();
		collider->SetSolid(false);
		collider->SetColliderType(Type::TankSpawnPointer);

		mInsertToMap(object, Layer::Front);

		object->RegisterObserver(&mQuadTreeObserver);
		mInsertToQuadTree(object.get());

		return object;
	}
}

