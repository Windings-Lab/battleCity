#include "PCHeader.h"

#include "GameManager.h"
#include "WorldManager.h"

namespace BattleCity::Manager
{
	GameManager::GameManager() : Manager(Type::Game), mGameOver(false), mGameOverState(false)
	{}

	GameManager& GameManager::GetInstance()
	{
		static GameManager single;
		return single;
	}

	void GameManager::StartUp()
	{
		mGameOver = false;
	}
	void GameManager::ShutDown()
	{
	}

	void GameManager::Step()
	{
		WM.Step();
	}

	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
}
