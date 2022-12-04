#include "WorldManager.h"

#include "TankPlayer.h"

namespace battleCity
{
	WorldManager::WorldManager() : Manager(ManagerType::World)
	{
		mPlayerID = 0;
	}

	WorldManager& WorldManager::GetInstance()
	{
		static WorldManager single;
		return single;
	}

	void WorldManager::StartUp()
	{
		std::unique_ptr<Object> player = std::make_unique<TankPlayer>();
		mPlayerID = player->ID;
		WM.InsertObject(player);
	}

	void WorldManager::ShutDown()
	{
		mWorldList.Clear();
	}

	void WorldManager::Step()
	{
		// Step All
		// Move All
		// Delete All
		// Draw All
	}

	void WorldManager::Draw()
	{
	}

	void WorldManager::InsertObject(std::unique_ptr<Object>& objPtr)
	{
		// Insert Movable Objects
		mWorldList.Insert(objPtr);
	}

	void WorldManager::RemoveObject(int objID)
	{
		mObjectsToMove.erase(objID);
		mWorldList.Remove(objID);
	}

	std::unordered_set<int> WorldManager::GetObjectsToMove() const
	{
		return mObjectsToMove;
	}

	std::unordered_set<int> WorldManager::GetObjectsOfType(Object::Type type) const
	{
		std::unordered_set<int> newList;
		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			if (objRef->ObjectType == type)
				newList.insert(objRef->ID);
		}

		return newList;
	}

	void WorldManager::MarkForDelete(int objID)
	{
		mObjectsToDelete.insert(objID);
	}
}
