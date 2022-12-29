#include "PCHeader.h"

#include "WorldManager.h"

#include "BasicObjectFactory.h"
#include "MapCreator.h"

#include "Object.h"

namespace BattleCity::Manager
{
	void WorldManager::OnInit()
	{
		__super::OnInit();

		InitMap();

#ifdef _DEBUG
		std::cout << "World Manager object count: " << mFrontLayer.GetSize() << "\n";
#endif
	}
	void WorldManager::OnClose()
	{
		mFrontLayer.Clear();
	}

	void WorldManager::InitMap()
	{
		Object::BasicObjectFactory objectFactory(*this);

		const auto worldBoundaries = objectFactory.CreateWorldBoundaries();

		int posX = 40, posY = 44;
		worldBoundaries->SetPosition(posX, posY);

		for (const auto& mapRow : MapCreator::GetLevel(R"(.\data\Maps\level1.txt)"))
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
