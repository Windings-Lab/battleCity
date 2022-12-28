#include "PCHeader.h"

#include "WorldManager.h"

#include "BasicObjectFactory.h"
#include "MapCreator.h"

#include "Object.h"

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
		auto& objectFactory = Object::BasicObjectFactory::GetInstance();

		const auto worldBoundaries = objectFactory.CreateWorldBoundaries();

		int posX = 40, posY = 44;
		worldBoundaries->SetPosition(posX, posY);

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
						const auto tankPlayer = objectFactory.CreateTank(Object::Type::TankPlayer);
						tankPlayer->SetPosition(posX, posY);
					}
					break;
				case Object::Type::TankNPC:
					{
						const auto tankNPC = objectFactory.CreateTank(Object::Type::TankNPC);
						tankNPC->SetPosition(posX, posY);
					}
					break;
				case Object::Type::Wall:
					{
						const auto wall = objectFactory.CreateWall();
						wall->SetPosition(posX, posY);
					}
					break;
				case Object::Type::Phoenix:
					{
						const auto phoenix = objectFactory.CreatePhoenix();
						phoenix->SetPosition(posX, posY);
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

	void updateTest(int test)
	{
		std::cout << "Test func called " << test << std::endl;
	}

	void WorldManager::Test()
	{
		ISignal<int> testSignal;

		testSignal.AddListener(updateTest);
		testSignal.AddListener([](int num){std::cout << "Test lambda called " << num << std::endl; });

		testSignal.Dispatch(1);
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
