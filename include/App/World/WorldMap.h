#pragma once

#include "ObjectContainer.h"

namespace BattleCity::Object
{
	class Object;
}

namespace BattleCity
{
	class Level;

	class WorldMap final
	{
	public:
		using TopLeft = Vector2Int;

	public:
		WorldMap() = default;

		DISALLOW_COPY_MOVE(WorldMap)

		~WorldMap() = default;

		void SetWorldRelative(const TopLeft& worldRelative) noexcept;
		const TopLeft& GetWorldRelative() const noexcept;

		void CreateMap(const Level& level);

		Object::Object& GetObject(int id) const;
		void InsertObject(std::unique_ptr<Object::Object>&& objPtr
			, Sprite::Layer layer = Sprite::Layer::Front);
		void MarkForDelete(int objID);

		const Object::ObjectContainer& GetBackLayer() const noexcept;
		const Object::ObjectContainer& GetFrontLayer() const noexcept;

	private:
		TopLeft mWorldRelative;

		Object::ObjectContainer mBackLayer;
		Object::ObjectContainer mFrontLayer;
	};
}
