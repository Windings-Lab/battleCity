#include "PCHeader.h"

#include "GameManager.h"
#include "WorldManager.h"

namespace BattleCity::Manager
{
	GameManager::GameManager() : Manager(Type::Game), mGameOver(false)
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
		WM.Step(mDeltaTime);
		mTime += mDeltaTime / 100.0;
	}

	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
	const float& GameManager::GetTime()
	{
		return mTime;
	}
}
