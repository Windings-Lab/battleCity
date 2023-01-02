#pragma once

#include "Game/Object/Container/Container.h"

namespace BattleCity::Object::World
{
	class Level;

	class Map final
	{
	public:
		using TopLeft = Vector2Int;

	public:
		Map() = default;

		DISALLOW_COPY_MOVE(Map)

		~Map() = default;

		void SetWorldRelative(const TopLeft& worldRelative) noexcept;
		const TopLeft& GetWorldRelative() const noexcept;

		void CreateMap(const Level& level);

		Object& GetObject(int id) const;
		Object* InsertObject(std::unique_ptr<Object>&& object
			, Sprite::Layer layer = Sprite::Layer::Front);
		void MarkForDelete(int objID);

		const Container& GetBackLayer() const noexcept;
		const Container& GetFrontLayer() const noexcept;

	private:
		TopLeft mWorldRelative;

		Container mBackLayer;
		Container mFrontLayer;
	};
}
