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
		// Private since a singleton
		WorldManager();
		// Don't allow copy
		WorldManager(WorldManager const&);
		// Don't allow assignment
		void operator=(WorldManager const&);

		std::vector<std::vector<Object*>> map;
		std::vector<std::vector<int>> powerUpPositions;
		// Objects, that need to update
		// every loop step
		ObjectList objectsToMove;
		// All Objects in game world
		// to check collision with
		ObjectList worldList;
		// List of all Objects to delete.
		ObjectList deletionList;

		static int worldID;
		static int moveID;

		Vector gameOverPos;
		Sprite* gameOverSpr;
		bool gameOver;

		int tankCount;
		int tankStorage;
		int killCount;

		PowerUp* powerUp;
		bool isPowerUp;
		bool powerUpisTaked;
	public:
		friend class Manager;
		friend class GameManager;

		~WorldManager();

		// Get the one and only instance of the WorldManager
		static WorldManager& getInstance();

		// Startup game world (initialize everything to empty)
        // Return 0
		int startUp(TankPlayer& newPlayer);

		// Shutdown game world (delete all game world Objects)
		void ShutDown() override;

		void setGameOverState();
		void setTankCount(int newTankCount);
		int getTankCount();

		// killCount += newKillCount;
		void setKillCount(int newKillCount);
		int getKillCount();

		// Insert Object into world
		// Return 0 if ok, else -1
		int insertObject(Object* objectPtr);

		// Remove Object from world
		// Return 0 if ok, else -1
		int removeObject(Object* objectPtr);

		// Return list of all Objects in world
		ObjectList getAllObjects() const;

		int getSizeOfWorldList();
		int getSizeOfMoveList();

		int getWorldID() const;
		int getMoveID() const;
		std::vector<std::vector<Object*>>& getWorldMap();
		std::vector<std::vector<int>>& getPowerUpPositions();

		void createSomeTanks();

		int initMap(TankPlayer& newPlayer);

		// Return list of Objects matching type
		// List is empty if none found
		ObjectList objectsOfType(std::string type);

		// Update world.
		// Update positions of Objects based on their velocities.
		void update();

		// Draw all Objects
		void draw();
		void drawBackground();

		/// Move Object.
		/// If collision with solid, send collision events.
		/// If no collision with solid, move ok.
		/// If all collided objects soft, move ok.
		/// If Object is spectral, move ok.
		/// If move ok, move.
		/// Return 0 if moved, else -1 if collision with solid.
		int moveObject(Object* ptrObject, Vector where);

		// Indicate Object is to be deleted at end of current game loop.
		// Return 0 if ok
		int markForDelete(Object* objectPtr);

		void createPowerUp();
		void setPowerUpToFalse();
		void setPowerUpisTakedToTrue();

		// Return list of Objects collided with at position 'where'.
		// Collisions only with solid and soft Objects.
		ObjectList getCollisions(const Object* ptrObject, Vector where) const;
	};
}

