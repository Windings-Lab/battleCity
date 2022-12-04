#include "Rectangle.h"

namespace battleCity
{
	Rectangle::Rectangle() : Rectangle(Vector2Int::Zero())
	{
	}
	Rectangle::Rectangle(Vector2Int position) : Rectangle(16, 16, position)
	{
	}
	Rectangle::Rectangle(int width, int height) : Rectangle(0, width, 0, height)
	{
	}
	Rectangle::Rectangle(int width, int height, Vector2Int position)
		: Rectangle(position.X, width, position.Y, height)
	{
	}
	Rectangle::Rectangle(int xMin, int xMax, int yMin, int yMax)
	{
		mPosition = Vector2Int(xMin, yMin);
		mSize = Vector2Int(xMax, yMax);
	}

	void Rectangle::SetPosition(Vector2Int position)
	{
		mPosition = position;
	}
	Vector2Int Rectangle::GetPosition() const
	{
		return mPosition;
	}
	int Rectangle::GetX() const
	{
		return mPosition.X;
	}
	int Rectangle::GetY() const
	{
		return mPosition.Y;
	}

	void Rectangle::SetSize(Vector2Int size)
	{
		mSize = size;
	}

	Vector2Int Rectangle::GetSize() const
	{
		return mSize;
	}
	int Rectangle::GetWidth() const
	{
		return mSize.X;
	}
	int Rectangle::GetHeight() const
	{
		return mSize.Y;
	}
}
