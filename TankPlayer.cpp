#include "TankPlayer.h"
#include "GameManager.h"


namespace battleCity
{
	TankPlayer::TankPlayer() : Tank(Type::TankPlayer)
	{
	}

	void TankPlayer::EventHandler(Event& event)
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
		GM.SetGameOverState();
	}
}
