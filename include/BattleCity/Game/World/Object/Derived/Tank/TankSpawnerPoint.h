#pragma once
#include "BattleCity/Engine/Timer.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Tank;

	namespace Factory
	{
		struct Standart;
	}

	namespace Component
	{
		class Collider;
	}

	class TankSpawnerPoint : public Object
	{
	public:
		explicit TankSpawnerPoint(const std::function<void(ID, Layer)>&);

		void SetTankCreator(Factory::Standart&);

		void Update() override;
		void ResolveCollisions(Object&) override;
		void NoCollision() override;
		void OnOutOfBounds(const Vector2Int&) override;

	private:
		void CreateTank();

	private:
		static int mTankCount;

		Component::Collider* mCollider;

		bool mSpawnBlocked;

		Engine::Timer mTimeToSpawn;
		std::function<std::shared_ptr<Tank>(Type, Position)> mTankCreator;

		std::mt19937 mRandomGenerator;
		std::uniform_int_distribution<int> mRandomDirection;
	};
}


