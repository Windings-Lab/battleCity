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
		Test();

#ifdef _DEBUG
		std::cout << "World Manager object count: " << mFrontLayer.GetSize() << "\n";
#endif
	}
	void WorldManager::ShutDown()
	{
		mFrontLayer.Clear();
	}

	void WorldManager::InitMap()
	{
		using std::make_unique;
		using std::unique_ptr;

		auto worldBoundaries = make_unique<Object::WorldBoundaries>();

		int posX = 40, posY = 44;
		worldBoundaries->SetPosition(posX, posY);
		worldBoundaries->SetSprite({ Sprite::Type::Background, Sprite::Behaviour::Basic });

		InsertObject(std::move(worldBoundaries), Sprite::Layer::Back);

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
						auto tankPlayer = make_unique<Object::Tank>();
						tankPlayer->SetPosition(posX, posY);
						tankPlayer->SetSprite({ Sprite::Type::TankPlayer, Sprite::Behaviour::Up });
						InsertObject(std::move(tankPlayer));
					}
					break;
				case Object::Type::TankNPC:
					{
						auto tank = make_unique<Object::Tank>();
						tank->SetPosition(posX, posY);
						tank->SetSprite({ Sprite::Type::TankNPC, Sprite::Behaviour::Up });
						InsertObject(std::move(tank));
					}
					break;
				case Object::Type::Wall:
					{
						auto wall = make_unique<Object::Wall>();
						wall->SetPosition(posX, posY);
						wall->SetSprite({ Sprite::Type::Wall, Sprite::Behaviour::Basic });
						InsertObject(std::move(wall));
					}
					break;
				case Object::Type::Phoenix:
					{
						auto phoenix = make_unique<Object::Phoenix>();
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

	void WorldManager::Test()
	{
	}

	Object::Object& WorldManager::GetObject(int id) const
	{
		return mFrontLayer.GetObject(id);
	}

	void WorldManager::InsertObject(std::unique_ptr<Object::Object>&& objPtr, Sprite::Layer layer)
	{
		switch (layer)
		{
		case Sprite::Layer::Back:
		{
			mBackLayer.Insert(std::move(objPtr));
			break;
		}
		case Sprite::Layer::Front:
		{
			mFrontLayer.Insert(std::move(objPtr));
			break;
		}
		case Sprite::Layer::UI:
		case Sprite::Layer::Error:
		default:
			break;
		}
	}
	void WorldManager::MarkForDelete(int objID)
	{

	}

	const Object::ObjectContainer& WorldManager::GetBackLayerObjects() const noexcept
	{
		return mBackLayer;
	}
	const Object::ObjectContainer& WorldManager::GetFrontLayerObjects() const noexcept
	{
		return mFrontLayer;
	}
}
