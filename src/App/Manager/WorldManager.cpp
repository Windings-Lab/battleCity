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

		unique_ptr<Object::Object> worldBoundaries = make_unique<Object::WorldBoundaries>();

		int posX = 40, posY = 44;
		worldBoundaries->SetPosition(posX, posY);
		worldBoundaries->SetSprite({ Sprite::Type::Background, Sprite::Behaviour::Basic });

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
						unique_ptr<Object::Object> tankPlayer = make_unique<Object::Tank>();
						tankPlayer->SetPosition(posX, posY);
						tankPlayer->SetSprite({ Sprite::Type::TankPlayer, Sprite::Behaviour::Up });
						InsertObject(std::move(tankPlayer));
					}
					break;
				case Object::Type::TankNPC:
					{
						unique_ptr<Object::Object> tank = make_unique<Object::Tank>();
						tank->SetPosition(posX, posY);
						tank->SetSprite({ Sprite::Type::TankNPC, Sprite::Behaviour::Up });
						InsertObject(std::move(tank));
					}
					break;
				case Object::Type::Wall:
					{
						unique_ptr<Object::Object> wall = make_unique<Object::Wall>();
						wall->SetPosition(posX, posY);
						wall->SetSprite({ Sprite::Type::Wall, Sprite::Behaviour::Basic });
						InsertObject(std::move(wall));
					}
					break;
				case Object::Type::Phoenix:
					{
						unique_ptr<Object::Object> phoenix = make_unique<Object::Phoenix>();
						phoenix->SetPosition(posX, posY);
						phoenix->SetSprite({ Sprite::Type::Phoenix, Sprite::Behaviour::Basic });
						InsertObject(std::move(phoenix));
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
