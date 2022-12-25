#pragma once

#include "Manager.h"
#include "ObjectList.h"

namespace BattleCity::Object
{
	class Object;
}

namespace BattleCity::Manager
{
	class WorldManager final : public Manager
	{
	private:
		WorldManager() = default;

	public:
		static WorldManager& GetInstance();

		WorldManager(WorldManager&&) = delete;
		WorldManager(const WorldManager&) = delete;

		void operator=(const WorldManager&) = delete;
		void operator=(WorldManager&&) = delete;

		~WorldManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		Object::Object& GetObject(int id) const;
		Object::ObjectList::Iterator& GetFrontLayerIterator();
		Object::ObjectList::Iterator& GetBackLayerIterator();

		void InsertObject(std::unique_ptr<Object::Object>&& objPtr
			, Sprite::Layer layer = Sprite::Layer::Front);
		void MarkForDelete(int objID);

	private:
		void InitMap();
		void Test();

		Object::ObjectList mBackLayer;
		Object::ObjectList mFrontLayer;
	};

	constexpr auto& WM = WorldManager::GetInstance;
}
