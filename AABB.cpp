#include "AABB.h"

namespace battleCity
{
	AABB::AABB() : AABB(Vector2Int::Zero())
	{
	}
	AABB::AABB(Vector2Int position) : AABB(16, 16, position)
	{
	}
	AABB::AABB(int width, int height) : AABB(0, width, 0, height)
	{
	}
	AABB::AABB(int width, int height, Vector2Int position)
		: AABB(position.X, width, position.Y, height)
	{
	}
	AABB::AABB(int xMin, int xMax, int yMin, int yMax)
	{
		mPosition = Vector2Int(xMin, yMin);
		mSize = Vector2Int(xMax, yMax);
	}

	void AABB::SetPosition(Vector2Int position)
	{
		mPosition = position;
	}
	Vector2Int AABB::GetPosition() const
	{
		return mPosition;
	}
	int AABB::GetX() const
	{
		return mPosition.X;
	}
	int AABB::GetY() const
	{
		return mPosition.Y;
	}

	void AABB::SetSize(Vector2Int size)
	{
		mSize = size;
	}

	Vector2Int AABB::GetSize() const
	{
		return mSize;
	}
	int AABB::GetWidth() const
	{
		return mSize.X;
	}
	int AABB::GetHeight() const
	{
		return mSize.Y;
	}
}
