#include "Screen.h"

namespace BattleCity
{
	Screen& Screen::GetInstance()
	{
		static Screen screen;
		return screen;
	}

	void Screen::Set(int width, int height, bool fullscreenMode)
	{
		mScreenBounds = Rectangle(width, height);
		mFullscreen = fullscreenMode;
	}

	int Screen::GetWidth() const
	{
		return mScreenBounds.W();
	}

	int Screen::GetHeight() const
	{
		return mScreenBounds.H();
	}

	bool Screen::GetFullscreen() const
	{
		return mFullscreen;
	}
}
