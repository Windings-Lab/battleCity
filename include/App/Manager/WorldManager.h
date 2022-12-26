#pragma once

#include "Manager.h"
#include "ObjectContainer.h"

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

		Object::Object& GetObject(int id) const noexcept;
		void InsertObject(std::unique_ptr<Object::Object>&& objPtr
			, Sprite::Layer layer = Sprite::Layer::Front) noexcept;
		void MarkForDelete(int objID);

		const Object::ObjectContainer& GetBackLayerObjects() const noexcept;
		const Object::ObjectContainer& GetFrontLayerObjects() const noexcept;

	private:
		void InitMap();
		void Test();

		Object::ObjectContainer mBackLayer;
		Object::ObjectContainer mFrontLayer;
	};

	constexpr auto& WM = WorldManager::GetInstance;
}
