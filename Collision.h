#pragma once
#include "Rectangle.h"

namespace battleCity
{
	struct Collision
	{
		Collision() = delete;
		~Collision() = delete;

		static bool AABB(Rectangle a, Rectangle b);
	};
}
