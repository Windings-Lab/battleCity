#pragma once

namespace battleCity
{
	class Screen
	{
	public:
		static Screen& GetInstance();

		Screen(const Screen&) = delete;
		Screen(Screen&&) = delete;

		void operator=(const Screen&) = delete;
		void operator=(Screen&&) = delete;

		~Screen() = default;

		int GetWidth();
		int GetHeight();
		bool GetFullscreen();

		void Set(int width, int height, bool fullscreenMode);

	private:
		Screen() = default;
		bool mFullscreen;
	};

	inline Screen& SCR = Screen::GetInstance();
}
