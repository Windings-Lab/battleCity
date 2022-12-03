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
		mScreenBounds = AABB(width, height);
		mFullscreen = fullscreenMode;
	}

	int Screen::GetWidth() const
	{
		return mScreenBounds.GetWidth();
	}

	int Screen::GetHeight() const
	{
		return mScreenBounds.GetHeight();
	}

	bool Screen::GetFullscreen() const
	{
		return mFullscreen;
	}
}
