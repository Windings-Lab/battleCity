#include "PCHeader.h"

#include "Rectangle.h"

namespace BattleCity::Engine::Physics
{
	Rectangle::Rectangle(const TopLeft& min, const BottomRight& max)
		: mPosition(min.X, min.Y)
		, mSize(max - min)
	{
	}

	Rectangle::Rectangle(X x, Y y, Width w, Height h)
		: mPosition(x, y)
		, mSize(w, h)
	{
	}

	bool Rectangle::Intersects(const Rectangle& other) const noexcept
	{
		return (GetX() <= other.GetX() + other.GetWidth() &&
			GetX() + GetWidth() >= other.GetX() &&
			GetY() <= other.GetY() + other.GetHeight() &&
			GetY() + GetHeight() >= other.GetY());
	}
	Vector2Int Rectangle::GetPenetration(const Rectangle& other) const noexcept
	{
		int left   = std::max(GetX(), other.GetX());
		int right  = std::min(GetX() + GetWidth(), other.GetX() + other.GetWidth());

		int top    = std::max(GetY(), other.GetY());
		int bottom = std::min(GetY() + GetHeight(), other.GetY() + other.GetHeight());

		return { std::max(left, right) - std::min(left, right) + 1
			     , std::max(top, bottom) - std::min(top, bottom) + 1 };
	}

	void Rectangle::SetPosition(const Position& position) noexcept
	{
		mPosition = position;
	}
	const Rectangle::Position& Rectangle::GetPosition() const noexcept
	{
		return mPosition;
	}
	Rectangle::X Rectangle::GetX() const noexcept
	{
		return mPosition.X;
	}
	Rectangle::Y Rectangle::GetY() const noexcept
	{
		return mPosition.Y;
	}

	void Rectangle::SetSize(const Size& size) noexcept
	{
		mSize = size;
	}
	const Rectangle::Size& Rectangle::GetSize() const noexcept
	{
		return mSize;
	}
	Rectangle::Width Rectangle::GetWidth() const noexcept
	{
		return mSize.X;
	}
	Rectangle::Height Rectangle::GetHeight() const noexcept
	{
		return mSize.Y;
	}

	Rectangle Rectangle::Get(Quadrant quad) const noexcept
	{
		switch (quad)
		{
			case Quadrant::TL: return TopLeftQuadrant();
			case Quadrant::TR: return TopRightQuadrant();
			case Quadrant::BL: return BottomLeftQuadrant();
			case Quadrant::BR: return BottomRightQuadrant();
			default: return TopLeftQuadrant();
		}
	}

	Rectangle::Position Rectangle::GetCenter() const noexcept
	{
		return { mPosition.X + (mSize.X >> 1), mPosition.Y + (mSize.Y >> 1) };
	}

	bool Rectangle::operator==(const Rectangle& other) const noexcept
	{
		return mPosition == other.mPosition && mSize == other.mSize;
	}
	bool Rectangle::operator!=(const Rectangle& other) const noexcept
	{
		return !(*this == other);
	}

	Rectangle Rectangle::TopLeftQuadrant() const noexcept
	{
		return Rectangle(mPosition.X, mPosition.Y, mSize.X >> 1, mSize.Y >> 1);
	}
	Rectangle Rectangle::TopRightQuadrant() const noexcept
	{
		return Rectangle(mPosition.X + (mSize.X >> 1), mPosition.Y, mSize.X >> 1, mSize.Y >> 1);
	}
	Rectangle Rectangle::BottomLeftQuadrant() const noexcept
	{
		return Rectangle(mPosition.X, mPosition.Y + (mSize.Y >> 1), mSize.X >> 1, mSize.Y >> 1);
	}
	Rectangle Rectangle::BottomRightQuadrant() const noexcept
	{
		return Rectangle(mPosition.X + (mSize.X >> 1), mPosition.Y + (mSize.Y >> 1), mSize.X >> 1, mSize.Y >> 1);
	}
}
