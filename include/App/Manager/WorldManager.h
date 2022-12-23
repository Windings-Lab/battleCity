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
		Object::ObjectList& GetObjectList();

		void InsertObject(std::unique_ptr<Object::Object>&& objPtr);
		void RemoveObject(int objID);
		void MarkForDelete(int objID);
	private:
		void InitMap();

	private:
		WorldManager();

		Object::ObjectList mObjectList;
	};

	constexpr auto& WM = WorldManager::GetInstance;
}
