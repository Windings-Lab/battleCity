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

		mMapCreator.CreateMap(R"(.\data\Maps\level1.txt)");
		mMapCreator.SetStartPosition({ 40, 44 });
		InitMap();

#ifdef _DEBUG
		std::cout << "World Manager object count: " << mFrontLayer.GetSize() << "\n";
#endif
	}
	void WorldManager::OnClose()
	{
		mFrontLayer.Clear();
	}

	const Vector2Int& WorldManager::GetWorldRelative() const noexcept
	{
		return mMapCreator.GetTopLeftPosition();
	}

	void WorldManager::InitMap()
	{
		Object::BasicObjectFactory objectFactory(*this);

		const auto worldBoundaries = objectFactory.CreateWorldBoundaries();

		auto& startPos = mMapCreator.GetTopLeftPosition();
		worldBoundaries->SetPosition(startPos);

		const auto& mapColumn = mMapCreator.GetMap();

		int nextPosY = startPos.Y;
		for (const auto& mapRow : mapColumn)
		{
			int nextPosX = startPos.X;
			for (const auto& objectType : mapRow)
			{
				Vector2Int position(nextPosX, nextPosY);
				switch (objectType)
				{
				case Object::Type::None: 
					break;
				case Object::Type::TankPlayer:
					{
						const auto tankPlayer = objectFactory.CreateTank(Object::Type::TankPlayer);
						tankPlayer->SetPosition(position);
					}
					break;
				case Object::Type::TankNPC:
					{
						const auto tankNPC = objectFactory.CreateTank(Object::Type::TankNPC);
						tankNPC->SetPosition(position);
					}
					break;
				case Object::Type::Wall:
					{
						const auto wall = objectFactory.CreateWall();
						wall->SetPosition(position);
					}
					break;
				case Object::Type::Phoenix:
					{
						const auto phoenix = objectFactory.CreatePhoenix();
						phoenix->SetPosition(position);
					}
					break;
				default: 
					break;
				}

				nextPosX += 16;
			}

			nextPosY += 16;
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
