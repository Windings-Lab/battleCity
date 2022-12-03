#include "AABB.h"

namespace battleCity
{
	AABB::AABB() : AABB(Vector2Int::Zero())
	{
	}
	AABB::AABB(Vector2Int position) : AABB(16, 16, position)
	{
	}

	AABB::AABB(int width, int height, Vector2Int position)
		: AABB(position.X, width, position.Y, height)
	{
	}

	AABB::AABB(int xMin, int xMax, int yMin, int yMax)
	{
		mMin = Vector2Int(xMin, yMin);
		mMax = Vector2Int(xMax, yMax);
	}
}
