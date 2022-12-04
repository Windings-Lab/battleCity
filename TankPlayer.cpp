#include "TankPlayer.h"

#include "Explosion.h"
#include "WorldManager.h"

#include "GameManager.h"


namespace battleCity
{
	TankPlayer::TankPlayer() : Tank(Type::TankPlayer)
	{
	}


	inline void TankPlayer::Draw()
	{
		// drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}

	void TankPlayer::EventHandler(Event& event)
	{

	}

	TankPlayer::~TankPlayer()
	{
		GM.SetGameOverState();
	}
}
