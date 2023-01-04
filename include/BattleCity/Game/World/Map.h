#pragma once

#include "BattleCity/NamespaceAliases.h"
#include "BattleCity/Game/Object/Container.h"

namespace BattleCity::Game::Object::World
{
	using TopLeft = Vector2Int;

	class Level;

	class Map final
	{
	public:
		Map() = default;

		DISALLOW_COPY_MOVE(Map)

		~Map() = default;

		void SetWorldRelative(const TopLeft& worldRelative) noexcept;
		const TopLeft& GetWorldRelative() const noexcept;

		void CreateMap(const Level& level);

		Object& GetObject(int id) const;
		Object* InsertObject(std::unique_ptr<Object>&& object
			, NSTexture::Layer layer = NSTexture::Layer::Front);
		void MarkForDelete(int objID);

		const Container& GetBackLayer() const noexcept;
		const Container& GetFrontLayer() const noexcept;

	private:
		TopLeft mWorldRelative;

		Container mBackLayer;
		Container mFrontLayer;
	};
}
