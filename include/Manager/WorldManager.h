#pragma once

#include "PCHeader.h"

#include "Manager.h"
#include "Object.h"
#include "ObjectList.h"

namespace BattleCity::Manager
{
	class WorldManager final : public Manager
	{
	public:
		// Singleton
		static WorldManager& GetInstance();

		WorldManager(WorldManager&&) = delete;
		WorldManager(const WorldManager&) = delete;

		void operator=(const WorldManager&) = delete;
		void operator=(WorldManager&&) = delete;

		~WorldManager() override = default;
	public:
		void StartUp() override;
		void ShutDown() override;
	public:
		void Step();

		Object& GetObject(int id);

		void InsertObject(std::unique_ptr<Object>& objPtr);
		void RemoveObject(int objID);
		void MarkForDelete(int objID);

		const std::unordered_set<int>& GetMovableObjects() const;
		// Expensive
		std::unordered_set<int> GetObjectsOfType(Object::Type type) const;
	private:
		void Update();
		void Draw();


	private:
		// Singleton
		WorldManager();

		// All Objects in game world
		ObjectList mWorldList;
		// Objects, that needed to move every loop step
		std::unordered_set<int> mMovableObjects;
		// List of all Objects to delete in the end of loop step.
		std::unordered_set<int> mObjectsToDelete;

		int mPlayerID;
	};

	inline WorldManager& WM = WorldManager::GetInstance();
}
