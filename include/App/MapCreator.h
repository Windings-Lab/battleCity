#pragma once

namespace BattleCity
{
	class MapCreator final
	{
	public:
		using Map = std::vector<std::vector<Object::Type>>;

	public:
		MapCreator() = default;

		DISALLOW_COPY_MOVE(MapCreator)

		~MapCreator() = default;

	public:
		void CreateMap(const char* levelPath);
		const Map& GetMap() const noexcept;

		void SetStartPosition(const Vector2Int& startPos) noexcept;
		const Vector2Int& GetTopLeftPosition() const noexcept;

		Map::const_iterator begin() const noexcept;
		Map::const_iterator end() const noexcept;

	private:
		Map mMap;
		Vector2Int mStartPos;
	};
}
