#include "PCHeader.h"
#include "WorldMap.h"

#include "WorldLevel.h"

#include "BattleCity/Framework/Screen.h"

#include "BattleCity/Game/World/Object/Object.h"
#include "Object/Containers/QuadTree.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Object/Derived/Tank/Tank.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Object/Derived/Phoenix.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Object/Derived/GameOver.h"

namespace BattleCity::Game::World
{
	Map::Map(const NSFramework::Screen& screen, const Engine::Texture::GroupLibrary& textureGroups, Object::QuadTree& quadTree)
		: mScreenBounds(0, 0, screen.GetWidth(), screen.GetHeight())
		, mWorldBounds(quadTree.GetBorder())
		, mObjectFactory(*this, quadTree, textureGroups)
		, mContainers(static_cast<int>(Object::Layer::Count))
		, mDeleters(static_cast<int>(Object::Layer::Count))
	{
	}

	std::shared_ptr<Object::Object> Map::GetPlayer() noexcept
	{
		return mPlayer.lock();
	}
	std::shared_ptr<Object::Object> Map::GetPhoenix() noexcept
	{
		return mPhoenix.lock();
	}

	void Map::CreateMap(const Level& level)
	{
		for (auto& container : mContainers)
		{
			container.Clear();
		}
		for (auto& deleter : mDeleters)
		{
			deleter.clear();
			mDeleterDuplicateCheck.clear();
		}

		mObjectFactory.CreateBackgrounds(mWorldBounds.GetPosition());

		const auto& mapColumn = level;
		int nextPosY = mWorldBounds.GetPosition().Y;
		for (const auto& mapRow : mapColumn)
		{
			int nextPosX = mWorldBounds.GetPosition().X;
			for (const auto& objectType : mapRow)
			{
				const Vector2Int position(nextPosX, nextPosY);
				switch (objectType)
				{
				case Object::Type::None: 
					break;
				case Object::Type::TankPlayer:
					{
						mPlayer = mObjectFactory.CreateTank(Object::Type::TankPlayer, position);
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
						mPhoenix = mObjectFactory.CreatePhoenix(position);
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
		std::cout << "Created map with: " << mContainers[static_cast<int>(Object::Layer::Middle)].GetSize() << " object count." << std::endl;
#endif
	}

	const Engine::Physics::Rectangle& Map::GetWorldBounds() const noexcept
	{
		return mWorldBounds;
	}

	const Engine::Physics::Rectangle& Map::GetScreenBounds() const noexcept
	{
		return mScreenBounds;
	}

	std::shared_ptr<Object::Object> Map::CreateObjectBy(Object::Type type)
	{
		switch (type)
		{
		case Object::Type::None:
		case Object::Type::TankPlayer:
		case Object::Type::TankNPC:
		case Object::Type::Bullet:
		case Object::Type::Wall:
		case Object::Type::Phoenix:
		case Object::Type::Explosion:
		case Object::Type::PowerUp:
		case Object::Type::WorldBoundaries:
			return nullptr;
		case Object::Type::GameOver:
			return mObjectFactory.CreateGameOver();
		case Object::Type::Error:
		default: return nullptr;
		}
	}

	std::shared_ptr<Object::Object> Map::GetObjectBy(Object::ID id, Object::Layer layer) const
	{
		return mContainers[static_cast<int>(layer)].GetObject(id);
	}

	void Map::InsertObject(std::shared_ptr<Object::Object> object, Object::Layer layer)
	{
		object->SetLayer(layer);

		mContainers[static_cast<int>(layer)].Insert(std::move(object));
	}

	void Map::MarkForDelete(Object::ID objID, Object::Layer layer)
	{
		if(!mDeleterDuplicateCheck.emplace(objID).second) return;

		mDeleters[static_cast<int>(layer)].push_back(objID);
	}
	void Map::DestroyObjects()
	{
		for (int layer = 0; layer < mDeleters.size(); layer++)
		{
			for (auto objectID : mDeleters[layer])
			{
				auto& container = mContainers.at(layer);
				auto object = container.GetObject(objectID);
				object->OnDestroy();
				container.RemoveBy(objectID);
			}

			mDeleters[layer].clear();
		}

		mDeleterDuplicateCheck.clear();
	}

	const Object::Container& Map::GetLayer(Object::Layer layer) const
	{
		return mContainers[static_cast<int>(layer)];
	}
	Object::Container& Map::GetDebugLayer()
	{
		return mContainers[static_cast<int>(Object::Layer::Debug)];
	}
}
