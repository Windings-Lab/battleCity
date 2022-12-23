#include "PCHeader.h"

#include "WorldManager.h"

#include "MapCreator.h"

#include "Object.h"
#include "Phoenix.h"
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
		using std::make_unique;
		using std::unique_ptr;

		int posX = 40, posY = 44;

		std::unique_ptr<Object::Object> worldBoundaries
			= std::make_unique<Object::WorldBoundaries>();

		worldBoundaries->SetPosition(40, 44);

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
					{
						unique_ptr<Object::Object> tank = make_unique<Object::Tank>();
						tank->SetPosition(posX, posY);
						InsertObject(std::move(tank));
					}
					break;
				case Object::Type::TankNPC:
					{
						unique_ptr<Object::Object> tank = make_unique<Object::Tank>();
						tank->SetPosition(posX, posY);
						InsertObject(std::move(tank));
					}
					break;
				case Object::Type::Wall:
					{
						unique_ptr<Object::Object> tank = make_unique<Object::Wall>();
						tank->SetPosition(posX, posY);
						InsertObject(std::move(tank));
					}
					break;
				case Object::Type::Phoenix:
					{
						unique_ptr<Object::Object> tank = make_unique<Object::Phoenix>();
						tank->SetPosition(posX, posY);
						InsertObject(std::move(tank));
					}
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
	void WorldManager::MarkForDelete(int objID)
	{

	}
}
