#include "Screen.h"

//Variables to Set
unsigned int Screen::_width = 0;
unsigned int Screen::_height = 0;
bool Screen::_fullscreen = false;

// boundaryL = 40
float Screen::_boundaryL = 0;
// boundaryL = 44
float Screen::_boundaryU = 0;

// boundaryR = 760
// 720 - last coordinate for creating wall
float Screen::_boundaryR = 0;
// boundaryD = 556
// 512 - last coordinate for creating wall
float Screen::_boundaryD = 0;

Screen& Screen::set(unsigned int wValue, unsigned int hValue, bool fValue) noexcept
{
	static Screen single;
	if (_width == 0 || _height == 0)
	{
		single._width = wValue;
		single._height = hValue;
		single._fullscreen = fValue;
		single._boundaryL = 40;
		single._boundaryU = 44;
		single._boundaryR = 800 - single._boundaryL;
		single._boundaryD = 600 - single._boundaryU;
	}
	return single;
}

Screen& Screen::getInstance()
{
	static Screen single;
	return single;
}

void Screen::boundaryRSet(unsigned int newWidth)
{
	_boundaryR = newWidth;
}

void Screen::boundaryDSet(unsigned int newHeight)
{
	_boundaryD = newHeight;
}

void Screen::boundaryLSet(unsigned int newWidth)
{
	_boundaryL = newWidth;
}

void Screen::boundaryUSet(unsigned int newHeight)
{
	_boundaryU = newHeight;
}

unsigned int Screen::getWidth()
{
	return _width;
}

unsigned int Screen::getHeight()
{
	return _height;
}

bool Screen::getFullscreen()
{
	return _fullscreen;
}


float Screen::getBoundaryR()
{
	return _boundaryR;
}

float Screen::getBoundaryD()
{
	return _boundaryD;
}

float Screen::getBoundaryL()
{
	return _boundaryL;
}

float Screen::getBoundaryU()
{
	return _boundaryU;
}
