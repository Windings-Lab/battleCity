#include "Screen.h"

namespace battleCity
{
	void Screen::Set(int width, int height, bool fullscreenMode)
	{
		mWidth = width;
		mHeight = height;
		mFullscreen = fullscreenMode;
	}

	unsigned int Screen::GetWidth()
	{
		return mWidth;
	}

	unsigned int Screen::GetHeight()
	{
		return mHeight;
	}

	bool Screen::GetFullscreen()
	{
		return mFullscreen;
	}
}
