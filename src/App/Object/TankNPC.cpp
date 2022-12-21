#include "PCHeader.h"
#include "TankNPC.h"

namespace BattleCity::Object
{
	TankNPC::TankNPC(int x, int y)
		: Tank(x, y, { Manager::SpriteType::TankNPC, Behaviour::Up })
	{
		mObjectType = Type::TankNPC;
	}

	void TankNPC::Fire()
	{

	}

	void TankNPC::Update()
	{
	}
}

