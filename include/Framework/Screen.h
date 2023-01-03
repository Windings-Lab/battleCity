#pragma once

namespace BFramework = BattleCity::Framework;

namespace BattleCity::Framework
{
	using ScreenWidth = int;
	using ScreenHeight = int;

	class Screen final
	{
	public:
		Screen(ScreenWidth&, ScreenHeight&, bool& fullscreen);

		int GetWidth() const noexcept;
		int GetHeight() const noexcept;

		bool IsFullscreen() const noexcept;

	private:
		ScreenWidth& mWidth;
		ScreenHeight& mHeight;
		bool& mFullScreen;

	};
}
