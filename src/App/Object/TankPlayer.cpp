#include "PCHeader.h"

#include "TankPlayer.h"

namespace BattleCity::Object
{
	TankPlayer::TankPlayer(int x, int y)
		: Tank(x, y, { Manager::SpriteType::TankPlayer, Behaviour::Up })
	{
		mObjectType = Type::TankPlayer;
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
