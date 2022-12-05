#include "Screen.h"

Screen::Screen() : mFullscreen(false)
{
}

Screen& Screen::GetInstance()
{
	static Screen screen;
	return screen;
}

void Screen::Set(int width, int height, bool fullscreenMode)
{
	mScreenBounds = BattleCity::Rectangle(width, height);
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
