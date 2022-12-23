#include "PCHeader.h"

#include "WorldManager.h"

#include "MapCreator.h"

#include "Object.h"
#include "PhoenixAndFlag.h"
#include "Tank.h"
#include "Wall.h"
#include "WorldBoundaries.h"

namespace BattleCity::Manager
{
	WorldManager& WorldManager::GetInstance()
	{
		static WorldManager single;
		return single;
	}
	WorldManager::WorldManager() : Manager(Type::World)
	{
	}

	void WorldManager::StartUp()
	{
		__super::StartUp();

		InitMap();

#ifdef _DEBUG
		std::cout << "World Manager object count: " << mObjectList.GetSize() << "\n";
#endif
	}
	void WorldManager::ShutDown()
	{
		mObjectList.Clear();
	}

	void WorldManager::InitMap()
	{
		std::unique_ptr<Object::Object> worldBoundaries
			= std::make_unique<Object::WorldBoundaries>(40, 44);

		int posX = worldBoundaries->X(), posY = worldBoundaries->Y();
		InsertObject(std::move(worldBoundaries));

		for (const auto& mapRow 
			: MapCreator::GetLevel(R"(.\data\Maps\level1.txt)"))
		{
			for (const auto& objectType : mapRow)
			{
				switch (objectType)
				{
				case Object::Type::None: 
					break;
				case Object::Type::TankPlayer:
					InsertObject(std::make_unique<Object::Tank>(posX, posY));
					break;
				case Object::Type::TankNPC:
					InsertObject(std::make_unique<Object::Tank>(posX, posY));
					break;
				case Object::Type::Wall:
					InsertObject(std::make_unique<Object::Wall>(posX, posY));
					break;
				case Object::Type::PhoenixAndFlag:
					InsertObject(std::make_unique<Object::PhoenixAndFlag>(posX, posY));
					break;
				default: 
					break;
				}
				posX += 16;
			}
			posX = 40;
			posY += 16;
		}
	}

	Object::Object& WorldManager::GetObject(int id) const
	{
		return mObjectList.GetObject(id);
	}

	Object::ObjectList& WorldManager::GetObjectList()
	{
		return mObjectList;
	}

	void WorldManager::InsertObject(std::unique_ptr<Object::Object>&& objPtr)
	{
		mObjectList.Insert(std::move(objPtr));
	}
	void WorldManager::RemoveObject(int objID)
	{
		mObjectList.Remove(objID);
	}
	void WorldManager::MarkForDelete(int objID)
	{

	}
}
