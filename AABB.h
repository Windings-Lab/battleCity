#pragma once

#include "Vector2Int.h"

namespace battleCity
{
	// Create AABBox at World position
	class AABB
	{
	public:
		// Create with default 16x16 vertexes
		// Position (0, 0)
		AABB();
		// Create with default 16x16 vertexes
		AABB(Vector2Int position);
		AABB(int width, int height, Vector2Int position);
		AABB(int xMin, int xMax, int yMin, int yMax);

	private:
		Vector2Int mMin;
		Vector2Int mMax;
	};
}
