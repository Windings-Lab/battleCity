#pragma once

namespace BattleCity
{
	class LevelCreator final
	{
	public:
		using Level = std::vector<std::vector<Object::Type>>;

	public:
		LevelCreator() = default;

		DISALLOW_COPY_MOVE(LevelCreator)

		~LevelCreator() = default;

	public:
		void CreateLevel(const char* levelPath);
		const Level& GetMap() const noexcept;

		void SetStartPosition(const Vector2Int& startPos) noexcept;
		const Vector2Int& GetTopLeftPosition() const noexcept;

		Level::const_iterator begin() const noexcept;
		Level::const_iterator end() const noexcept;

	private:
		Level mMap;
		Vector2Int mStartPos;
	};
}
