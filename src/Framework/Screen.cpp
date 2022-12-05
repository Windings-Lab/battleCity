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

bool Screen::IsValidSize(int w, int h) const
{
	return 
		w >= 800 && w <= 1920
		&&
		h >= 600 && h <= 1080;
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
