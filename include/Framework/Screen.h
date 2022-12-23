#pragma once

namespace BattleCity::Framework::Screen
{
	int W();
	int H();
	const bool& IsFullscreen();
	void Set(int width, int height, bool fullScreen);
	bool IsValidSize(int w, int h);
}
