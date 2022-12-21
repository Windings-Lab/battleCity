#include "PCHeader.h"

#include "PhoenixAndFlag.h"

namespace BattleCity::Object
{
	PhoenixAndFlag::PhoenixAndFlag(int x, int y)
		: Object(x, y, Type::PhoenixAndFlag, { Manager::SpriteType::Phoenix, Behaviour::Basic })
	{
	}

	void PhoenixAndFlag::Update()
	{

	}
}
