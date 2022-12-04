#pragma once

#include <memory>
#include <unordered_set>

#include "Manager.h"
#include "Object.h"
#include "ObjectList.h"

namespace battleCity
{
	class WorldManager final : public Manager
	{
	public:
		// Singleton
		static WorldManager& GetInstance();

		WorldManager(WorldManager&&) = delete;
		WorldManager(const WorldManager&) = delete;

		void operator=(const WorldManager&) = delete;
		void operator=(WorldManager&&) = delete;

		~WorldManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		void Step();
		void Draw();

		Object& GetObject(int id);

		void InsertObject(std::unique_ptr<Object>& objPtr);
		void RemoveObject(int objID);
		void MarkForDelete(int objID);

		std::unordered_set<int> GetObjectsToMove() const;
		std::unordered_set<int> GetObjectsOfType(Object::Type type) const;
	private:
		// Singleton
		WorldManager();

		// All Objects in game world
		ObjectList mWorldList;
		// Objects, that need to update every loop step
		std::unordered_set<int> mObjectsToMove;
		// List of all Objects to delete.
		std::unordered_set<int> mObjectsToDelete;

		int mPlayerID;
	};

	inline WorldManager& WM = WorldManager::GetInstance();
}
