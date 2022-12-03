#pragma once

#include "Vector2Int.h"

namespace battleCity
{
	// Create AABBox at World position
	class AABB
	{
	public:
		// Width		= 16
		// Height		= 16
		// Position		= (0, 0)
		AABB();
		// Width		= 16
		// Height		= 16
		// Position		= position
		AABB(Vector2Int position);
		// Width		= width
		// Height		= height
		// Position		= (0, 0)
		AABB(int width, int height);
		AABB(int width, int height, Vector2Int position);
		AABB(int xMin, int xMax, int yMin, int yMax);

		Vector2Int GetPosition() const;

		Vector2Int GetSize() const;
		int GetWidth() const;
		int GetHeight() const;

	private:
		Vector2Int mPosition;
		Vector2Int mSize;
	};
}
