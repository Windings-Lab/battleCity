#include "PCHeader.h"

#include "Rectangle.h"

namespace BattleCity
{
	Rectangle::Rectangle() : Rectangle(Vector2Int(0, 0)) {}

	Rectangle::Rectangle(const Vector2Int& position)
		: Rectangle(position.X, position.Y, 16, 16) {}

	Rectangle::Rectangle(int width, int height)
		: Rectangle(0, 0, width, height) {}

	Rectangle::Rectangle(int x, int y, int width, int height)
		: mPosition(x, y)
		, mSize(width, height)
	{}

	bool Rectangle::Intersects(const Rectangle& other) const noexcept
	{
		return
			std::max(X(), other.X())
			< std::min(X() + W(), other.X() + other.W())
			& std::max(Y(), other.Y())
			< std::min(Y() + H(), other.Y() + other.H());
	}

	void Rectangle::SetPosition(int x, int y)
	{
		mPosition.SetXY(x, y);
	}
	const Vector2Int& Rectangle::GetPosition() const
	{
		return mPosition;
	}
	int Rectangle::X() const
	{
		return mPosition.X;
	}
	int Rectangle::Y() const
	{
		return mPosition.Y;
	}

	void Rectangle::SetSize(int width, int height)
	{
		mSize.SetXY(width, height);
	}
	const Vector2Int& Rectangle::GetSize() const
	{
		return mSize;
	}
	int Rectangle::W() const
	{
		return mSize.X;
	}
	int Rectangle::H() const
	{
		return mSize.Y;
	}
}
