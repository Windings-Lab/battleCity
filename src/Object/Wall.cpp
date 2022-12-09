#include "PCHeader.h"

#include "Wall.h"

namespace BattleCity::Object
{
	Wall::Wall(int x, int y)
		: Object(x, y, Type::Wall, Manager::SpriteType::Wall, Behaviour::Basic)

	{

	}

	void Wall::Update()
	{

	}
}