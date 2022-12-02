#pragma once

#include <unordered_set>

#include "Manager.h"
#include "Vector.h"
#include "Object.h"
#include "ObjectList.h"

#define WM battleCity::WorldManager::GetInstance()

namespace battleCity
{
	class WorldManager : public Manager
	{
	private:
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
		bool mGameOver;

		int mTankCount;
		int mTankStorage;
		int mKillCount;

		int mPowerUpID;
		bool mIsPowerUp;
		bool mPowerUpTaked;
	public:
		friend class Manager;
		friend class GameManager;

		WorldManager(WorldManager const&) = delete;
		void operator=(WorldManager const&) = delete;

		~WorldManager();

		// Get the one and only instance of the WorldManager
		static WorldManager& GetInstance();

		// Startup game world (initialize everything to empty)
        // Return 0
		int StartUp(Object& newPlayer);

		// Shutdown game world (delete all game world Objects)
		void ShutDown() override;

		void SetGameOverState();
		void SetTankCount(int newTankCount);
		int GetTankCount();

		// killCount += newKillCount;
		void SetKillCount(int newKillCount);
		int GetKillCount();

		// Insert Object into world
		// Return 0 if ok, else -1
		int InsertObject(const std::unique_ptr<Object>& objPtr);

		// Remove Object from world
		// Return 0 if ok, else -1
		int RemoveObject(int objID);

		// Return list of all Objects in world
		const ObjectList& GetAllObjects() const;

		int GetSizeOfWorldList() const;

		std::vector<std::vector<int>>& GetWorldMap();
		std::vector<std::vector<int>>& GetPowerUpPositions();

		void CreateSomeTanks();

		int InitMap(Object& newPlayer);

		// Return list of Objects matching type
		// List is empty if none found
		std::unordered_set<int> GetObjectsOfType(Object::Type type) const;

		// Update world.
		// Update positions of Objects based on their velocities.
		void Update();

		// Draw all Objects
		void Draw();
		void DrawBackground();

		/// Move Object.
		/// If collision with solid, send collision events.
		/// If no collision with solid, move ok.
		/// If all collided objects soft, move ok.
		/// If Object is spectral, move ok.
		/// If move ok, move.
		/// Return 0 if moved, else -1 if collision with solid.
		int MoveObject(Object& movableObj, Vector where);

		// Indicate Object is to be deleted at end of current game loop.
		// Return 0 if ok
		int MarkForDelete(int objID);

		void CreatePowerUp();
		void SetPowerUpToFalse();
		void SetPowerUpisTakedToTrue();

		// Return list of Objects collided with at some position
		// Collisions only with solid and soft Objects.
		std::unordered_set<int> GetCollisions(const Object& ptrObject, Vector where) const;
	};
}

