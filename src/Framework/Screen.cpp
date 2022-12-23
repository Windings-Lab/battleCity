#include "PCHeader.h"

#include "Screen.h"

#include <Rectangle.h>

namespace BattleCity::Framework::Screen
{
	namespace
	{
		Rectangle Bounds;
		bool FullScreen;
	}

	int W()
	{
		return Bounds.W();
	}

	int H()
	{
		return Bounds.H();
	}

	const bool& IsFullscreen()
	{
		return FullScreen;
	}

	void Set(int width, int height, bool fullScreen)
	{
		Bounds.SetSize(width, height);
		FullScreen = fullScreen;
	}

	bool IsValidSize(int w, int h)
	{
		return
			w >= 800 && w <= 1920
			&&
			h >= 600 && h <= 1080;
	}
}
