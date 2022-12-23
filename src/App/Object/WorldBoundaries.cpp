#include "PCHeader.h"
#include "WorldBoundaries.h"

namespace BattleCity::Object
{
	WorldBoundaries::WorldBoundaries(int x, int y)
		: Object(x, y, { Manager::SpriteType::Background, Behaviour::Basic })
	{

	}
}

