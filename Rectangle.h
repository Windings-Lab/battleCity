#pragma once

#include "Vector2Int.h"

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
		// Position		= position
		Rectangle(Vector2Int position);
		// Width		= width
		// Height		= height
		// Position		= (0, 0)
		Rectangle(int width, int height);
		Rectangle(int width, int height, Vector2Int position);
		Rectangle(int xMin, int xMax, int yMin, int yMax);

		void SetPosition(Vector2Int position);
		Vector2Int GetPosition() const;
		int GetX() const;
		int GetY() const;

		void SetSize(Vector2Int size);
		Vector2Int GetSize() const;
		int GetWidth() const;
		int GetHeight() const;

	private:
		Vector2Int mPosition;
		Vector2Int mSize;
	};
}
