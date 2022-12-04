#pragma once

namespace battleCity
{
	// Create Rectangle at World position
	class Rectangle
	{
	public:
		// Width		= 16
		// Height		= 16
		// Position		= (0, 0)
		Rectangle();
		// Width		= 16
		// Height		= 16
		// Position		= (x, y)
		Rectangle(int x, int y);
		Rectangle(int x, int y, int width, int height);

		int X() const;
		int Y() const;

		int W() const;
		int H() const;

	private:
		int mX, mY;
		int mW, mH;
	};
}
