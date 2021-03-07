#include "Screen.h"

unsigned int Screen::_width = NULL;
unsigned int Screen::_height = NULL;
bool Screen::_fullscreen = NULL;

const unsigned int& Screen::width = Screen::_width;
const unsigned int& Screen::height = Screen::_height;
const bool& Screen::fullscreen = Screen::_fullscreen;

Screen& Screen::set(unsigned int wValue, unsigned int hValue, bool fValue) noexcept
{
	static Screen single;
	if (_width == NULL || _height == NULL)
	{
		single._width = wValue;
		single._height = hValue;
		single._fullscreen = fValue;
	}
	return single;
}

Screen::~Screen()
{
#if DEBUG == 2
	cout << "Screen destructor" << endl;
#endif
}