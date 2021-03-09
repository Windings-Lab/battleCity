#pragma once

#include "Manager.h"
#include "Vector.h"

#define WM battleCity::WorldManager::getInstance()

namespace battleCity
{
	class WorldManager : public Manager
	{
	private:
		// Private since a singleton
		WorldManager();
		// Don't allow copy
		WorldManager(WorldManager const&);
		// Don't allow assignment
		void operator=(WorldManager const&);

		// All Objects in game world
		ObjectList worldList;
		// List of all Objects to delete.
		ObjectList deletionList;

	public:
		friend class GameManager;
		friend class Manager;

		~WorldManager();

		// Get the one and only instance of the WorldManager
		static WorldManager& getInstance();

		// Startup game world (initialize everything to empty)
        // Return 0
		int startUp() override;

		// Shutdown game world (delete all game world Objects)
		void shutDown() override;

		// Insert Object into world
		// Return 0 if ok, else -1
		int insertObject(Object* objectPtr);

		// Remove Object from world
		// Return 0 if ok, else -1
		int removeObject(Object* objectPtr);

		// Return list of all Objects in world
		ObjectList getAllObjects() const;

		// Return list of Objects matching type
		// List is empty if none found
		ObjectList objectsOfType(string type);

		// Update world.
		// Update positions of Objects based on their velocities.
		// Lastly, delete Objects marked for deletion.
		void update();

		// Draw all Objects in view
		// Draw bottom up, from 0 to MAX_ALTITUDE
		void draw();

		/// Move Object. 
		/// If collision with solid, send collision events.
		/// If no collision with solid, move ok.
		/// If all collided objects soft, move ok.
		/// If Object is spectral, move ok.
		/// If move ok, move.
		/// If moved, adjust view if following this Object.
		/// If moved from inside world boundary to outside, generate EventOut.
		/// Return 0 if moved, else -1 if collision with solid.
		int moveObject(Object* ptrObject, Vector where);

		// Indicate Object is to be deleted at end of current game loop.
		// Return 0 if ok, else -1.
		int markForDelete(Object* objectPtr);
	};
}

