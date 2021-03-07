#pragma once
#include "Framework.h"

class Screen
{
public:
	virtual ~Screen();
	static const unsigned int& width;
	static const unsigned int& height;
	static const bool& fullscreen;

	/// <summary>
	/// Initialize screen
	/// </summary>
	/// <param name="">Width</param>
	/// <param name="">Height</param>
	/// <param name="">Fullscreen</param>
	/// <returns></returns>
	static Screen& set(unsigned int wValue, unsigned int hValue, bool fValue) noexcept;

private:
	Screen() {}
	Screen(const Screen&); // copy constructor
	Screen(Screen&&); // move constructor
	void operator=(Screen const&);

	static unsigned int _width;
	static unsigned int _height;
	static bool _fullscreen;
};