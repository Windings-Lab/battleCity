#pragma once

#include "Vector2Int.h"

class AABB
{
public:
	// Set default 16x16 vertexes
	AABB();
	AABB(int width, int height);
	AABB(int xMin, int xMax, int yMin, int yMax);

private:
	battleCity::Vector2Int mMin;
	battleCity::Vector2Int mMax;
};
