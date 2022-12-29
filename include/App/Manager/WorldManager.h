#pragma once

#include "Manager.h"
#include "ObjectContainer.h"

namespace BattleCity
{
	class MapCreator;
}

namespace BattleCity::Object
{
	class Object;
}

namespace BattleCity::Manager
{
	class WorldManager final : public Manager
	{
	public:
		using Manager::Manager;

		DISALLOW_COPY_MOVE(WorldManager)

		~WorldManager() override = default;

		void OnInit() override;
		void OnClose() override;

		Object::Object& GetObject(int id) const;
		void InsertObject(std::unique_ptr<Object::Object>&& objPtr
			, Sprite::Layer layer = Sprite::Layer::Front);
		void MarkForDelete(int objID);

		const Object::ObjectContainer& GetBackLayerObjects() const noexcept;
		const Object::ObjectContainer& GetFrontLayerObjects() const noexcept;

	private:
		void InitMap(const MapCreator& mapCreator);

		Object::ObjectContainer mBackLayer;
		Object::ObjectContainer mFrontLayer;
	};
}
