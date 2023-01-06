#include "PCHeader.h"
#include "WorldMap.h"

#include "WorldLevel.h"

#include "BattleCity/Game/World/Object/Object.h"

#include "Object/Derived/Phoenix.h"
#include "Object/Derived/Tank.h"
#include "Object/Derived/Wall.h"
#include "Object/Derived/WorldBoundaries.h"

namespace BattleCity::Game::World
{
	Map::Map(const Engine::Texture::GroupLibrary& textureGroups)
		: mObjectFactory(*this, textureGroups)
	{}
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

		const auto worldBoundaries = mObjectFactory.CreateWorldBoundaries();

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
						const auto& object = mObjectFactory.CreateTank(Object::Type::TankPlayer);
						object->SetPosition(position);
						object->SetBulletCount(1);
						object->Fire();
					}
					break;
				case Object::Type::TankNPC:
					{
						const auto object = mObjectFactory.CreateTank(Object::Type::TankNPC);
						object->SetPosition(position);
					}
					break;
				case Object::Type::Wall:
					{
						const auto object = mObjectFactory.CreateWall();
						object->SetPosition(position);
					}
					break;
				case Object::Type::Phoenix:
					{
						const auto object = mObjectFactory.CreatePhoenix();
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

	Object::Object& Map::GetObjectBy(Object::ID id) const
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
	void Map::MarkForDelete(Object::ID objID)
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
