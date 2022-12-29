#pragma once

#include "LevelCreator.h"
#include "ObjectContainer.h"

namespace BattleCity::Object
{
	class Object;
}

namespace BattleCity
{
	class WorldMap final
	{
	public:
		WorldMap() = default;

		DISALLOW_COPY_MOVE(WorldMap)

		~WorldMap() = default;

		void CreateLevel(const char* levelPath);

		const Vector2Int& GetWorldRelative() const noexcept;
		void SetWorldRelative(const Vector2Int& worldRelative) noexcept;

		void InitLevel();

		Object::Object& GetObject(int id) const;
		void InsertObject(std::unique_ptr<Object::Object>&& objPtr
			, Sprite::Layer layer = Sprite::Layer::Front);
		void MarkForDelete(int objID);

		const Object::ObjectContainer& GetBackLayer() const noexcept;
		const Object::ObjectContainer& GetFrontLayer() const noexcept;

	private:
		LevelCreator mMapCreator;

		Object::ObjectContainer mBackLayer;
		Object::ObjectContainer mFrontLayer;
	};
}
