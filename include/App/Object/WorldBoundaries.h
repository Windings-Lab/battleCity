#pragma once

#include "Object.h"

namespace BattleCity::Object
{
	class WorldBoundaries final : public Object
	{
	public:
		WorldBoundaries(int x, int y);
	};
}
