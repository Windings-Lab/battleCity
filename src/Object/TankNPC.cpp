#include "PCHeader.h"
#include "TankNPC.h"

namespace BattleCity::Object
{
	TankNPC::TankNPC(int x, int y)
		: Tank(x, y, Type::TankNPC, Manager::SpriteType::TankNPC, Behaviour::Up)
	{

	}

	void TankNPC::Fire()
	{

	}

	void TankNPC::Update()
	{
	}
}

