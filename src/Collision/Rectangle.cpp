#include "PCHeader.h"

#include "Rectangle.h"

namespace BattleCity
{
	Rectangle::Rectangle() : Rectangle(Vector2Int::Zero())
	{
	}
	Rectangle::Rectangle(Vector2Int position) : Rectangle(16, 16, std::move(position))
	{
	}
	Rectangle::Rectangle(int width, int height) : Rectangle(0, width, 0, height)
	{
	}
	Rectangle::Rectangle(int width, int height, Vector2Int position)
		: Rectangle(position.X(), width, position.Y(), height)
	{
	}
	Rectangle::Rectangle(int xMin, int xMax, int yMin, int yMax)
	{
		mPosition = Vector2Int(xMin, yMin);
		mSize = Vector2Int(xMax, yMax);
	}

	bool Rectangle::Intersects(const Rectangle& other)
	{
		return
			std::max(X(), other.X())
			< std::min(X() + W(), other.X() + other.W())
			& std::max(Y(), other.Y())
			< std::min(Y() + H(), other.Y() + other.H());
	}

	void Rectangle::SetPosition(int x, int y)
	{
		mPosition.SetX(x);
		mPosition.SetY(y);
	}
	const Vector2Int& Rectangle::GetPosition() const
	{
		return mPosition;
	}
	const int& Rectangle::X() const
	{
		return mPosition.X();
	}
	const int& Rectangle::Y() const
	{
		return mPosition.Y();
	}

	void Rectangle::SetSize(int width, int height)
	{
		mSize.SetX(width);
		mSize.SetY(height);
	}
	const Vector2Int& Rectangle::GetSize() const
	{
		return mSize;
	}
	const int& Rectangle::W() const
	{
		return mSize.X();
	}
	const int& Rectangle::H() const
	{
		return mSize.Y();
	}
}
