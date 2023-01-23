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

	bool Rectangle::OutOfInner(const Rectangle& bounds, Vector2Int& penetration) const noexcept
	{
		int left	= GetX();
		int right	= GetX() + GetWidth();
		int top		= GetY();
		int bottom	= GetY() + GetHeight();

		int boundsLeft		= bounds.GetX();
		int boundsRight		= bounds.GetX() + bounds.GetWidth();
		int boundTop		= bounds.GetY();
		int boundsBottom	= bounds.GetY() + bounds.GetHeight();

		if(left < boundsLeft)
		{
			penetration.X = boundsLeft - left;
			return true;
		}
		if(right > boundsRight)
		{
			penetration.X = -(right - boundsRight);
			return true;
		}

		if(top < boundTop)
		{
			penetration.Y = boundTop - top;
			return true;
		}
		if(bottom > boundsBottom)
		{
			penetration.Y = -(bottom - boundsBottom);
			return true;
		}

		return false;
	}
	bool Rectangle::OutOfInner(const Rectangle& bounds) const noexcept
	{
		int left = GetX();
		int right = GetX() + GetWidth();
		int top = GetY();
		int bottom = GetY() + GetHeight();

		int boundsLeft = bounds.GetX();
		int boundsRight = bounds.GetX() + bounds.GetWidth();
		int boundTop = bounds.GetY();
		int boundsBottom = bounds.GetY() + bounds.GetHeight();

		if (left < boundsLeft)
		{
			return true;
		}
		if (right > boundsRight)
		{
			return true;
		}

		if (top < boundTop)
		{
			return true;
		}
		if (bottom > boundsBottom)
		{
			return true;
		}

		return false;
	}
	bool Rectangle::Intersects(const Rectangle& other) const noexcept
	{
		return GetX()				< other.GetX() + other.GetWidth()
			&& GetX() + GetWidth()	> other.GetX()
			&& GetY()				< other.GetY() + other.GetHeight()
			&& GetY() + GetHeight() > other.GetY();
	}
	Vector2Int Rectangle::GetPenetration(const Rectangle& other) const noexcept
	{
		int right = GetX() + GetWidth();
		int otherRight = other.GetX() + other.GetWidth();
		int bottom = GetY() + GetHeight();
		int otherBottom = other.GetY() + other.GetHeight();

		int x_overlap = std::max(0, std::min(right, otherRight) - std::max(GetX(), other.GetX()));
		int y_overlap = std::max(0, std::min(bottom, otherBottom) - std::max(GetY(), other.GetY()));

		return { x_overlap * (GetX() > other.GetX() ? 1 : -1),
					y_overlap * (GetY() > other.GetY() ? 1 : -1) };
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
		return Rectangle(mPosition.X
						, mPosition.Y
						, mSize.X >> 1
						, mSize.Y >> 1);
	}
	Rectangle Rectangle::TopRightQuadrant() const noexcept
	{
		std::div_t halfWidth = std::div(mSize.X, 2);

		return Rectangle(mPosition.X + halfWidth.quot
						 , mPosition.Y
						 , mSize.X - halfWidth.quot + halfWidth.rem
						 , mSize.Y >> 1);
	}
	Rectangle Rectangle::BottomLeftQuadrant() const noexcept
	{
		std::div_t halfHeight = std::div(mSize.Y, 2);

		return Rectangle(mPosition.X
					 , mPosition.Y + halfHeight.quot
					 , mSize.X >> 1
					 , mSize.Y - halfHeight.quot + halfHeight.rem);
	}
	Rectangle Rectangle::BottomRightQuadrant() const noexcept
	{
		std::div_t halfWidth = std::div(mSize.X, 2);
		std::div_t halfHeight = std::div(mSize.Y, 2);

		return Rectangle(mPosition.X + halfWidth.quot
						,mPosition.Y + halfHeight.quot
						,mSize.X - halfWidth.quot + halfWidth.rem
						,mSize.Y - halfHeight.quot + halfHeight.rem);
	}
}
