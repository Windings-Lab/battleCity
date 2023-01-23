#include "PCHeader.h"
#include "WorldMap.h"

#include "WorldLevel.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "Object/Containers/QuadTree.h"

#include "Object/Derived/Tank.h"

namespace BattleCity::Game::World
{
	Map::Map(const Engine::Texture::GroupLibrary& textureGroups, Object::QuadTree& quadTree)
		: mBounds(quadTree.GetBorder())
		, mObjectFactory(*this, quadTree, textureGroups)
	{
	}

	std::shared_ptr<Object::Object> Map::CreateMap(const Level& level)
	{
		mFrontLayer.Clear();
		mBackLayer.Clear();

		mObjectFactory.CreateWorldBoundaries(mBounds.GetPosition());

		std::shared_ptr<Object::Tank> player = nullptr;

		const auto& mapColumn = level;
		int nextPosY = mBounds.GetPosition().Y;
		for (const auto& mapRow : mapColumn)
		{
			int nextPosX = mBounds.GetPosition().X;
			for (const auto& objectType : mapRow)
			{
				const Vector2Int position(nextPosX, nextPosY);
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
		std::cout << "Created map with: " << mFrontLayer.GetSize() << " object count." << std::endl;
#endif

		return player;
	}

	const Engine::Physics::Rectangle& Map::GetBounds() const noexcept
	{
		return mBounds;
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
		case Object::Layer::Debug:
		{
			mDebugLayer.Insert(std::move(object));
			break;
		}
		case Object::Layer::Error:
		default:
			break;
		}
	}

	void Map::MarkForDelete(Object::ID objID)
	{
		if(mDeleterDuplicateCheck.emplace(objID).second)
		{
			mDeleters.push_back(objID);
		}
	}
	void Map::DestroyObjects()
	{
		for (auto objectID : mDeleters)
		{
			auto object = mFrontLayer.GetObject(objectID);
			object->OnDestroy();
			mFrontLayer.RemoveBy(objectID);
		}

		mDeleters.clear();
		mDeleterDuplicateCheck.clear();
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

	Object::Container& Map::GetDebugLayer()
	{
		return mDebugLayer;
	}
}
