#include "PCHeader.h"

#include "TankPlayer.h"

namespace BattleCity::Object
{
	TankPlayer::TankPlayer(int x, int y)
		: Tank(x, y, Type::TankPlayer, { Manager::SpriteType::TankPlayer, Behaviour::Up })
	{

	}

	void TankPlayer::Update()
	{

	}

	void TankPlayer::Fire()
	{
		
	}

	TankPlayer::~TankPlayer()
	{
		
	}
}
