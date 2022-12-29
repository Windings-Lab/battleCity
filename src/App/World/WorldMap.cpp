#include "PCHeader.h"

#include "WorldMap.h"

#include "BasicObjectFactory.h"
#include "LevelCreator.h"

#include "Object.h"

namespace BattleCity
{
	void WorldMap::CreateLevel(const char* levelPath)
	{
		mMapCreator.CreateLevel(levelPath);
	}

	const Vector2Int& WorldMap::GetWorldRelative() const noexcept
	{
		return mMapCreator.GetTopLeftPosition();
	}
	void WorldMap::SetWorldRelative(const Vector2Int& worldRelative) noexcept
	{
		mMapCreator.SetStartPosition(worldRelative);
	}

	void WorldMap::InitLevel()
	{
		mFrontLayer.Clear();
		mBackLayer.Clear();

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

	Object::Object& WorldMap::GetObject(int id) const
	{
		return mFrontLayer.GetObject(id);
	}

	void WorldMap::InsertObject(std::unique_ptr<Object::Object>&& objPtr, Sprite::Layer layer)
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
	void WorldMap::MarkForDelete(int objID)
	{

	}

	const Object::ObjectContainer& WorldMap::GetBackLayer() const noexcept
	{
		return mBackLayer;
	}
	const Object::ObjectContainer& WorldMap::GetFrontLayer() const noexcept
	{
		return mFrontLayer;
	}
}
