#include "PCHeader.h"

#include "WorldManager.h"

#include "MapManager.h"

#include "Object.h"
#include "PhoenixAndFlag.h"
#include "TankNPC.h"
#include "TankPlayer.h"
#include "Wall.h"

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
		__super::StartUp();

		InitMap();

#ifdef _DEBUG
		std::cout << "World Manager object count: " << mWorldList.GetSize() << "\n";
#endif
	}
	void WorldManager::ShutDown()
	{
		mWorldList.Clear();
		mMovableObjects.clear();
		mObjectsToDelete.clear();
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

	void WorldManager::InitMap()
	{
		int posX = MAP().mBoundaries.X();
		int posY = MAP().mBoundaries.Y();
		for (const auto& mapRow : MAP().mMap)
		{
			for (const auto& objectType : mapRow)
			{
				std::unique_ptr<Object::Object> object = nullptr;
				switch (objectType)
				{
				case Object::Type::None: 
					break;
				case Object::Type::TankPlayer:
					object = std::make_unique<Object::TankPlayer>(posX, posY);
					InsertObject(object.release());
					break;
				case Object::Type::TankNPC:
					object = std::make_unique<Object::TankNPC>(posX, posY);
					InsertObject(object.release());
					break;
				case Object::Type::Wall:
					object = std::make_unique<Object::Wall>(posX, posY);
					InsertObject(object.release());
					break;
				case Object::Type::PhoenixAndFlag:
					object = std::make_unique<Object::PhoenixAndFlag>(posX, posY);
					InsertObject(object.release());
					break;
				default: 
					break;
				}

				posX += 16;
			}

			posY += 16;
			posX = MAP().mBoundaries.X();
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

	void WorldManager::InsertObject(Object::Object* objPtr)
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
