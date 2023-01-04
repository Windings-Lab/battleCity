#include "PCHeader.h"

#include "WorldMap.h"
#include "WorldLevel.h"

#include "BattleCity/Game/Object/Object.h"
#include "BattleCity/Game/Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Game::Object::World
{
	void Map::SetWorldRelative(const TopLeft& worldRelative) noexcept
	{
		mWorldRelative.SetXY(worldRelative);
	}
	const TopLeft& Map::GetWorldRelative() const noexcept
	{
		return mWorldRelative;
	}

	void Map::CreateMap(const Level& level)
	{
		mFrontLayer.Clear();
		mBackLayer.Clear();

		Factory::Standart objectFactory(*this);

		const auto worldBoundaries = objectFactory.CreateWorldBoundaries();

		worldBoundaries->SetPosition(mWorldRelative);

		const auto& mapColumn = level;

		int nextPosY = mWorldRelative.Y;
		for (const auto& mapRow : mapColumn)
		{
			int nextPosX = mWorldRelative.X;
			for (const auto& objectType : mapRow)
			{
				Vector2Int position(nextPosX, nextPosY);
				switch (objectType)
				{
				case Type::None: 
					break;
				case Type::TankPlayer:
					{
						const auto object = objectFactory.CreateTank(Type::TankPlayer);
						object->SetPosition(position);
					}
					break;
				case Type::TankNPC:
					{
						const auto object = objectFactory.CreateTank(Type::TankNPC);
						object->SetPosition(position);
					}
					break;
				case Type::Wall:
					{
						const auto object = objectFactory.CreateWall();
						object->SetPosition(position);
					}
					break;
				case Type::Phoenix:
					{
						const auto object = objectFactory.CreatePhoenix();
						object->SetPosition(position);
					}
					break;
				default: 
					break;
				}

				nextPosX += 16;
			}

			nextPosY += 16;
		}
#ifdef _DEBUG
		std::cout << "Created map with: " << mFrontLayer.GetSize() + mBackLayer.GetSize() << " object count." << std::endl;
#endif
	}

	Object& Map::GetObject(int id) const
	{
		return mFrontLayer.GetObject(id);
	}

	Object* Map::InsertObject(std::unique_ptr<Object>&& object, Layer layer)
	{
		auto objectPtr = object.get();

		switch (layer)
		{
		case Layer::Back:
		{
			mBackLayer.Insert(std::move(object));
			break;
		}
		case Layer::Front:
		{
			mFrontLayer.Insert(std::move(object));
			break;
		}
		case Layer::UI:
		case Layer::Error:
		default:
			objectPtr = nullptr;
			break;
		}

		return objectPtr;
	}
	void Map::MarkForDelete(int objID)
	{

	}

	const Container& Map::GetBackLayer() const noexcept
	{
		return mBackLayer;
	}
	const Container& Map::GetFrontLayer() const noexcept
	{
		return mFrontLayer;
	}
}
