#include "Collision.h"

#include <cmath>

namespace battleCity
{
	bool Collision::AABB(Rectangle a, Rectangle b)
	{
		using std::abs;

		if (abs(a.X()))
	}
}

/*
int TestAABBAABB(AABB a, AABB b)
{
if (Abs(a.c[0] - b.c[0]) > (a.r[0] + b.r[0])) return 0;
if (Abs(a.c[1] - b.c[1]) > (a.r[1] + b.r[1])) return 0;
if (Abs(a.c[2] - b.c[2]) > (a.r[2] + b.r[2])) return 0;
return 1;
}
 */