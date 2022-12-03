#pragma once

namespace battleCity
{
	class Screen
	{
	public:
		static Screen Instance;

		Screen(const Screen&) = delete;
		Screen(Screen&&) = delete;

		void operator=(const Screen&) = delete;
		void operator=(Screen&&) = delete;

		~Screen() = default;

		unsigned int GetWidth();
		unsigned int GetHeight();
		bool GetFullscreen();

		void Set(int width, int height, bool fullscreenMode);

	private:
		Screen();
		static unsigned int mWidth;
		static unsigned int mHeight;
		static bool mFullscreen;
	};
}
