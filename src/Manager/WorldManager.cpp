#include "PCHeader.h"

#include "WorldManager.h"

#include "Bullet.h"
#include "GameManager.h"
#include "Screen.h"
#include "TankPlayer.h"

namespace BattleCity::Manager
{
	WorldManager& WorldManager::GetInstance()
	{
		static WorldManager single;
		return single;
	}
	WorldManager::WorldManager() : Manager(Type::World)
	{
		mPlayerID = 0;
	}

	void WorldManager::StartUp()
	{
		// std::unique_ptr<Object> player = std::make_unique<TankPlayer>();
		// mPlayerID = player->ID;
		// WM.InsertObject(player);

		std::unique_ptr<Object::Object> bullet = std::make_unique<Object::Bullet>(Object::Type::Error);
		bullet->SetPosition(0, SCR.GetHeight() / 2);
		WM.InsertObject(bullet);
	}
	void WorldManager::ShutDown()
	{
		mWorldList.Clear();
	}

	void WorldManager::Step()
	{
		Update();
		// Delete All
		Draw();
	}

	void WorldManager::Draw()
	{
		for (auto& [id, obj] : mWorldList.GetRange())
		{
			obj->Draw();
		}
	}

	void WorldManager::Update()
	{
		for (auto& [id, obj] : mWorldList.GetRange())
		{
			obj->Update();
		}
	}

	Object::Object& WorldManager::GetObject(int id)
	{
		return mWorldList.GetObject(id);
	}

	void WorldManager::InsertObject(std::unique_ptr<Object::Object>& objPtr)
	{
		// Insert Movable Objects
		mWorldList.Insert(objPtr);
	}
	void WorldManager::RemoveObject(int objID)
	{
		mMovableObjects.erase(objID);
		mWorldList.Remove(objID);
	}
	void WorldManager::MarkForDelete(int objID)
	{
		mObjectsToDelete.insert(objID);
	}

	const std::unordered_set<int>& WorldManager::GetMovableObjects() const
	{
		return mMovableObjects;
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
}
