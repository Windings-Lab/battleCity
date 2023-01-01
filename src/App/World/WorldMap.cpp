#include "PCHeader.h"

#include "WorldMap.h"

#include "BasicObjectFactory.h"
#include "Level.h"

#include "Object.h"

namespace BattleCity
{
	void WorldMap::SetWorldRelative(const TopLeft& worldRelative) noexcept
	{
		mWorldRelative.SetXY(worldRelative);
	}
	const WorldMap::TopLeft& WorldMap::GetWorldRelative() const noexcept
	{
		return mWorldRelative;
	}

	void WorldMap::CreateMap(const Level& level)
	{
		mFrontLayer.Clear();
		mBackLayer.Clear();

		Object::BasicObjectFactory objectFactory(*this);

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

	Object::Object& WorldMap::GetObject(int id) const
	{
		return mFrontLayer.GetObject(id);
	}

	Object::Object* WorldMap::InsertObject(std::unique_ptr<Object::Object>&& object, Sprite::Layer layer)
	{
		auto objectPtr = object.get();

		switch (layer)
		{
		case Sprite::Layer::Back:
		{
			mBackLayer.Insert(std::move(object));
			break;
		}
		case Sprite::Layer::Front:
		{
			mFrontLayer.Insert(std::move(object));
			break;
		}
		case Sprite::Layer::UI:
		case Sprite::Layer::Error:
		default:
			objectPtr = nullptr;
			break;
		}

		return objectPtr;
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
