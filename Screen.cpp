#include "Screen.h"

namespace battleCity
{
	Screen& Screen::GetInstance()
	{
		static Screen screen;
		return screen;
	}

	void Screen::Set(int width, int height, bool fullscreenMode)
	{
		mWidth = width;
		mHeight = height;
		mFullscreen = fullscreenMode;
	}

	int Screen::GetWidth() const
	{
		return mWidth;
	}

	int Screen::GetHeight() const
	{
		return mHeight;
	}

	bool Screen::GetFullscreen() const
	{
		return mFullscreen;
	}
}
