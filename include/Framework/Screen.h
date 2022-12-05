#pragma once

#include "Rectangle.h"

class Screen
{
public:
	static Screen& GetInstance();

	Screen(const Screen&) = delete;
	Screen(Screen&&) = delete;

	void operator=(const Screen&) = delete;
	void operator=(Screen&&) = delete;

	~Screen() = default;

	bool IsValidSize(int w, int h) const;

	int GetWidth() const;
	int GetHeight() const;
	bool GetFullscreen() const;

	void Set(int width, int height, bool fullscreenMode);

private:
	Screen();
	BattleCity::Rectangle mScreenBounds;
	bool mFullscreen;
};

inline Screen& SCR = Screen::GetInstance();
