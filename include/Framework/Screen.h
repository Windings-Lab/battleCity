#pragma once

#include "Rectangle.h"

namespace BattleCity::Framework::Screen
{
	namespace 
	{
		BattleCity::Rectangle Bounds;
		bool FullScreen;
	}

	const int& W()
	{
		return Bounds.W();
	}

	const int& H()
	{
		return Bounds.H();
	}

	const bool& IsFullscreen()
	{
		return FullScreen;
	}

	void Set(int width, int height, bool fullScreen)
	{
		Bounds = BattleCity::Rectangle(width, height);
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
