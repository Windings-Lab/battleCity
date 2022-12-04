#pragma once

#include <unordered_set>

#include "Manager.h"
#include "Object.h"
#include "ObjectList.h"

namespace battleCity
{
	class WorldManager final : Manager
	{
	private:
		void InitMap();
		void CreateSomeTanks();
	public:
		WorldManager(WorldManager&&) = delete;
		WorldManager(const WorldManager&) = delete;

		void operator=(const WorldManager&) = delete;
		void operator=(WorldManager&&) = delete;

		~WorldManager() override = default;

		// Singleton
		static WorldManager& GetInstance();

		void StartUp() override;
		void ShutDown() override;

		// Update world.
		void Update();

		// Draw all Objects
		void Draw();
		void DrawBackground();

		void InsertObject(std::unique_ptr<Object>& objPtr);
		void RemoveObject(int objID);
		// Indicate Object is to be deleted at end of current game loop.
		void MarkForDelete(int objID);

		const ObjectList& GetAllObjects() const;
		std::unordered_set<int> GetObjectsToMove() const;
		std::unordered_set<int> GetObjectsOfType(Object::ObjectType type) const;
		int GetObjectCount() const;

		void SetPlayerID(int playerID);
		int GetPlayerID() const;

		void SetPlayerHealthToZero() const;

		void IncrementTankCount(int count);
		int GetTankCount();

		void IncrementKillCount(int newKillCount = 1);
		int GetKillCount();

		std::vector<std::vector<int>>& GetWorldMap();
		std::vector<std::vector<int>>& GetPowerUpPositions();

		void MoveObject(Object& movableObj, Vector where);
		// Return list of Objects collided with at some position
		std::unordered_set<int> GetCollisions(const Object& ptrObject, Vector where) const;

		void CreatePowerUp();
		void SetPowerUpToFalse();
		void SetPowerUpisTakedToTrue();
	private:
		// Singleton
		WorldManager();

		std::vector<std::vector<int>> mMap;
		std::vector<std::vector<int>> mPowerUpPositions;

		// All Objects in game world
		ObjectList mWorldList;
		// Objects, that need to update every loop step
		std::unordered_set<int> mObjectIDsToMove;
		// List of all Objects to delete.
		std::unordered_set<int> mObjectIDsToDelete;

		Vector mGameOverPos;
		Sprite* mGameOverSpr;

		int mPlayerID;
		int mTankCount;
		int mTankStorage;
		int mKillCount;

		int mPowerUpID;
		bool mIsPowerUp;
		bool mPowerUpTaked;
	};

	inline WorldManager& WM = WorldManager::GetInstance();
}

