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

		DISALLOW_COPY_MOVE(WorldManager)

		~WorldManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		Object::Object& GetObject(int id) const;
		void InsertObject(std::unique_ptr<Object::Object>&& objPtr
			, Sprite::Layer layer = Sprite::Layer::Front);
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
