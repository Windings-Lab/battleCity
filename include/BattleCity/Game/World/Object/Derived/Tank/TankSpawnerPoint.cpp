#include "PCHeader.h"
#include "TankSpawnerPoint.h"

#include "Tank.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Game::World::Object
{
	int TankSpawnerPoint::mTankCount = 0;

	TankSpawnerPoint::TankSpawnerPoint(const Position& pos, const std::function<void(ID, Layer)>& d)
		: Object(pos, d)
		, mCollider(AddComponent<Component::Collider>())
		, mSpawnBlocked(false)
		, mRandomGenerator(std::random_device{}())
		, mRandomDirection(0, 3)
	{
		mTimeToSpawn.StartOnce(5, [this]
			{
				CreateTank();
			});
	}

	void TankSpawnerPoint::SetTankCreator(Factory::Standart& factory)
	{
		mTankCreator = [&](Type type, Position pos) { return factory.CreateTank(type, pos); };
	}

	void TankSpawnerPoint::Update()
	{
		mTimeToSpawn.Repeat();
	}

	void TankSpawnerPoint::ResolveCollisions(Object& other)
	{
		auto otherCollider = other.GetComponent<Component::Collider>();
		if (!otherCollider->IsSolid())
		{
			mSpawnBlocked = false;
			return;
		}

		mSpawnBlocked = true;
	}

	void TankSpawnerPoint::NoCollision()
	{
		mSpawnBlocked = false;
	}

	void TankSpawnerPoint::OnOutOfBounds(const Vector2Int& vector2Int)
	{
		mSpawnBlocked = true;
	}

	void TankSpawnerPoint::CreateTank()
	{
		if(mTankCount >= 10) return;

		if (mSpawnBlocked)
		{
#ifdef _DEBUG
			std::cout << "Spawner blocked" << std::endl;
#endif
			return;
		}

		auto tank = mTankCreator(Type::TankNPC, this->GetPosition());
		auto randomDirectionIndex = mRandomDirection(mRandomGenerator);
		auto movable = tank->GetComponent<Component::Movable>();
		movable->SetMovementDirection(static_cast<Direction>(randomDirectionIndex));
		mTankCount++;
	}
}

