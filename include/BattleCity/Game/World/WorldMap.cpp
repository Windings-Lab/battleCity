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
	Map::Map(Relative pos, const Engine::Texture::GroupLibrary& textureGroups)
		: mObjectFactory(*this, textureGroups)
		, mWorldRelative(pos)
	{}
	void Map::SetWorldRelative(const Relative& worldRelative) noexcept
	{
		mWorldRelative = worldRelative;
	}
	const Relative& Map::GetWorldRelative() const noexcept
	{
		return mWorldRelative;
	}

	std::shared_ptr<Object::Object> Map::CreateMap(const Level& level)
	{
		mFrontLayer.Clear();
		mBackLayer.Clear();

		auto worldBoundaries = mObjectFactory.CreateWorldBoundaries();
		worldBoundaries->SetPosition(mWorldRelative);

		std::shared_ptr<Object::Tank> player = nullptr;

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
						player = mObjectFactory.CreateTank(Object::Type::TankPlayer, position);
					}
					break;
				case Object::Type::TankNPC:
					{
						auto object = mObjectFactory.CreateTank(Object::Type::TankNPC, position);
					}
					break;
				case Object::Type::Wall:
					{
						auto object = mObjectFactory.CreateWall(position);
					}
					break;
				case Object::Type::Phoenix:
					{
						auto object = mObjectFactory.CreatePhoenix(position);
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

		return player;
	}

	std::shared_ptr<Object::Object> Map::GetObjectBy(Object::ID id) const
	{
		return mFrontLayer.GetObject(id);
	}

	void Map::InsertObject(std::shared_ptr<Object::Object> object, Object::Layer layer)
	{
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
		{
			mUILayer.Insert(std::move(object));
			break;
		}
		case Object::Layer::Error:
		default:
			break;
		}
	}
	void Map::MarkForDelete(Object::ID objID)
	{
	}

	const Object::Container& Map::GetLayer(Object::Layer layer) const
	{
		switch (layer)
		{
		case Object::Layer::Error:
			throw std::runtime_error("Error when trying to get object layer list");
		case Object::Layer::Back:
			return mBackLayer;
		case Object::Layer::Front:
			return mFrontLayer;
		case Object::Layer::UI:
			return mUILayer;
		default:
			return mFrontLayer;
		}
	}
}
