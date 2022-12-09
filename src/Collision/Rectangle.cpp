#include "PCHeader.h"

#include "Rectangle.h"

namespace BattleCity
{
	Rectangle::Rectangle() : Rectangle(Vector2Int::Zero())
	{
	}
	Rectangle::Rectangle(Vector2Int position) : Rectangle(16, 16, position.X(), position.Y())
	{
	}
	Rectangle::Rectangle(int width, int height) : Rectangle(width, height, 0, 0)
	{
	}
	Rectangle::Rectangle(int x, int y, int width, int height)
		: mPosition(x, y), mSize(width, height)
	{
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
