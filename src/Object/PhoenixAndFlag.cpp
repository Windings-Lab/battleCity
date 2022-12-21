#include "PCHeader.h"

#include "PhoenixAndFlag.h"

namespace BattleCity::Object
{
	PhoenixAndFlag::PhoenixAndFlag(int x, int y)
		: Object(x, y, { Manager::SpriteType::Phoenix, Behaviour::Basic })
	{
		mObjectType = Type::PhoenixAndFlag;
	}

	void PhoenixAndFlag::Update()
	{

	}
}
