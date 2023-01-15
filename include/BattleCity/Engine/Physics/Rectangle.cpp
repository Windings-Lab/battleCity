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
		return
			std::max(GetX(), other.GetX())
			< std::min(GetX() + GetWidth(), other.GetX() + other.GetWidth())
			& std::max(GetY(), other.GetY())
			< std::min(GetY() + GetHeight(), other.GetY() + other.GetHeight());
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
