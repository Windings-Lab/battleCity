#include "GameManager.h"

#include "WorldManager.h"

namespace battleCity
{
	GameManager::GameManager() : Manager(ManagerType::Game), mGameOver(false), mGameOverState(false)
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
		WM.Draw();
	}

	void GameManager::SetGameOverState()
	{
		mGameOverState = true;
	}
	bool GameManager::GetGameOverState() const
	{
		return mGameOverState;
	}
	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
}
