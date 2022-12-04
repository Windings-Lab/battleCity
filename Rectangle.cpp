#include "Rectangle.h"

namespace battleCity
{
	Rectangle::Rectangle() : Rectangle(0, 0) {}
	Rectangle::Rectangle(int x, int y) : Rectangle(x, y, 16, 16) {}
	Rectangle::Rectangle(int x, int y, int width, int height) : mX(x), mY(y), mW(width), mH(height)
	{}

	void Rectangle::SetPosition(int x, int y)
	{
		mX = x;
		mY = y;
	}
	int Rectangle::X() const
	{
		return mX;
	}
	int Rectangle::Y() const
	{
		return mY;
	}

	int Rectangle::W() const
	{
		return mW;
	}
	int Rectangle::H() const
	{
		return mH;
	}
}
