#include "PCHeader.h"

#include "Screen.h"

namespace BattleCity::Framework
{
	Screen::Screen(ScreenWidth& w, ScreenHeight& h, bool& fullscreen)
		: mWidth(w)
		, mHeight(h)
		, mFullScreen(fullscreen)
	{
		const bool isValidWidth	 = w >= 800 && w <= 1920;
		const bool isValidHeight = h >= 600 && h <= 1080;
		const bool isValidSize   = isValidWidth && isValidHeight;

		if(!isValidSize)
		{
			throw std::invalid_argument("Invalid screen size");
		}
	}

	int Screen::GetWidth() const noexcept
	{
		return mWidth;
	}
	int Screen::GetHeight() const noexcept
	{
		return mHeight;
	}

	bool Screen::IsFullscreen() const noexcept
	{
		return mFullScreen;
	}
}
