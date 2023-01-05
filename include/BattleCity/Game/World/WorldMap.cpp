#include "PCHeader.h"

#include "WorldMap.h"
#include "WorldLevel.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "BattleCity/Game/World/Object/Factory/ObjectFactoryStandart.h"

namespace BattleCity::Game::World
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

		Object::Factory::Standart objectFactory(*this);

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
				case Object::Type::None: 
					break;
				case Object::Type::TankPlayer:
					{
						const auto object = objectFactory.CreateTank(Object::Type::TankPlayer);
						object->SetPosition(position);
					}
					break;
				case Object::Type::TankNPC:
					{
						const auto object = objectFactory.CreateTank(Object::Type::TankNPC);
						object->SetPosition(position);
					}
					break;
				case Object::Type::Wall:
					{
						const auto object = objectFactory.CreateWall();
						object->SetPosition(position);
					}
					break;
				case Object::Type::Phoenix:
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

	Object::Object& Map::GetObject(int id) const
	{
		return mFrontLayer.GetObject(id);
	}

	Object::Object* Map::InsertObject(std::unique_ptr<Object::Object>&& object, Object::Layer layer)
	{
		auto objectPtr = object.get();

		switch (layer)
		{
		case Object::Layer::Back:
		{
			mBackLayer.Insert(std::move(object));
			break;
		}
		case Object::Layer::Front:
		{
			mFrontLayer.Insert(std::move(object));
			break;
		}
		case Object::Layer::UI:
		case Object::Layer::Error:
		default:
			objectPtr = nullptr;
			break;
		}

		return objectPtr;
	}
	void Map::MarkForDelete(int objID)
	{

	}

	const Object::Container& Map::GetBackLayer() const noexcept
	{
		return mBackLayer;
	}
	const Object::Container& Map::GetFrontLayer() const noexcept
	{
		return mFrontLayer;
	}
}
