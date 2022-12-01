#pragma once

#include <string>

#include "Manager.h"
#include "Vector.h"
#include "Object.h"
#include "ObjectList.h"
#include "TankPlayer.h"
#include "PowerUp.h"

#define WM battleCity::WorldManager::getInstance()

namespace battleCity
{
	class PowerUp;
	class WorldManager : public Manager
	{
	private:
		std::vector<std::vector<Object*>> mMap;
		std::vector<std::vector<int>> mPowerUpPositions;
		// Objects, that need to update
		// every loop step
		ObjectList mObjectsToMove;
		// All Objects in game world
		// to check collision with
		ObjectList mWorldList;
		// List of all Objects to delete.
		ObjectList mDeletionList;

		static int mWorldId;
		static int mOveId;

		Vector mGameOverPos;
		Sprite* mGameOverSpr;
		bool mGameOver;

		int mTankCount;
		int mTankStorage;
		int mKillCount;

		PowerUp* mPowerUp;
		bool mIsPowerUp;
		bool mPowerUpTaked;
	public:
		friend class Manager;
		friend class GameManager;

		WorldManager() = delete;
		WorldManager(WorldManager const&) = delete;
		void operator=(WorldManager const&) = delete;

		~WorldManager();

		// Get the one and only instance of the WorldManager
		static WorldManager& GetInstance();

		// Startup game world (initialize everything to empty)
        // Return 0
		int StartUp(TankPlayer& newPlayer);

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
		int InsertObject(Object* objectPtr);

		// Remove Object from world
		// Return 0 if ok, else -1
		int RemoveObject(Object* objectPtr);

		// Return list of all Objects in world
		ObjectList GetAllObjects() const;

		int GetSizeOfWorldList();
		int GetSizeOfMoveList();

		int GetWorldId() const;
		int GetMoveId() const;
		std::vector<std::vector<Object*>>& GetWorldMap();
		std::vector<std::vector<int>>& GetPowerUpPositions();

		void CreateSomeTanks();

		int InitMap(TankPlayer& newPlayer);

		// Return list of Objects matching type
		// List is empty if none found
		ObjectList ObjectsOfType(std::string type);

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
		int MoveObject(Object* ptrObject, Vector where);

		// Indicate Object is to be deleted at end of current game loop.
		// Return 0 if ok
		int MarkForDelete(Object* objectPtr);

		void CreatePowerUp();
		void SetPowerUpToFalse();
		void SetPowerUpisTakedToTrue();

		// Return list of Objects collided with at position 'where'.
		// Collisions only with solid and soft Objects.
		ObjectList GetCollisions(const Object* ptrObject, Vector where) const;
	};
}

