#include "PCHeader.h"

#include "Rectangle.h"

namespace BattleCity::Engine::Physics
{
	Rectangle::Rectangle(const TopLeft& min, const BottomRight& max)
		: mPosition(min.X, min.Y)
		, mSize(max - min)
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

	void Rectangle::SetPosition(const Position& position)
	{
		mPosition = position;
	}
	const Rectangle::Position& Rectangle::GetPosition() const
	{
		return mPosition;
	}
	Rectangle::X Rectangle::GetX() const
	{
		return mPosition.X;
	}
	Rectangle::Y Rectangle::GetY() const
	{
		return mPosition.Y;
	}

	void Rectangle::SetSize(const Size& size)
	{
		mSize = size;
	}
	const Rectangle::Size& Rectangle::GetSize() const
	{
		return mSize;
	}
	Rectangle::Width Rectangle::GetWidth() const
	{
		return mSize.X;
	}
	Rectangle::Height Rectangle::GetHeight() const
	{
		return mSize.Y;
	}
}
