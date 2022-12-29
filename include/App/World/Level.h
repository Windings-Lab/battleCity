#pragma once

namespace BattleCity
{
	class Level final
	{
	public:
		using LevelSheet = std::vector<std::vector<Object::Type>>;

	private:
		explicit Level(LevelSheet levelSheet);

	public:
		Level() = delete;

		DISALLOW_COPY_MOVE(Level)

		~Level() = default;

		static Level CreateLevel(const char* levelPath);

		LevelSheet::const_iterator begin() const noexcept;
		LevelSheet::const_iterator end() const noexcept;

	private:
		friend void swap(Level&, Level&) noexcept;

	private:
		LevelSheet mLevelSheet;

	};
}
