#include "GameManager.h"
#include "WorldManager.h"
#include "TankPlayer.h"
#include "EventStep.h"
#include "Clock.h"
#include "Sprites.h"
#include "Framework.h"

namespace battleCity
{
	GameManager::GameManager() : Manager(ManagerType::Game)
	{
		mGameOver = false;
		mFrameTime = 0;
		mStepCount = 0;
	}

	void GameManager::SetGameOverState()
	{
		SetCustomStepCount(0);
		WM.SetPlayerHealthToZero();
		mGameOverState = true;
	}

	bool GameManager::GetGameOverState() const
	{
		return mGameOverState;
	}

	GameManager& GameManager::GetInstance()
	{
		static GameManager single;
		return single;
	}

	int GameManager::SpriteInit()
	{
		return SPR.initAll();
	}

	void GameManager::StartUp()
	{
		SpriteInit();
		mGameOver = false;
	}

	void GameManager::ShutDown()
	{
		mGameOver = true;
	}

	bool GameManager::GameOverTimerEnded()
	{
		if (mCustomStepCount >= 500)
		{
			mGameOver = true;
		}
		return mGameOver;
	}

	void GameManager::Update()
	{
		mClock.delta();
		EventStep eventStep;
		SendEvent(eventStep);
		WM.Update();
		WM.Draw();
		mFrameTime = getTickCount() / 1000;
		mStepCount++;
		mCustomStepCount++;

		mClock.sleep(mClock.split());
	}

	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
	int GameManager::GetStepCount() const
	{
		return mStepCount;
	}
	void GameManager::SetCustomStepCount(int stepCount)
	{
		mCustomStepCount = stepCount;
	}
	int GameManager::GetCustomStepCount() const
	{
		return mCustomStepCount;
	}
}
