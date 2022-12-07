#include "PCHeader.h"

#include "GameManager.h"

#include "TimerManager.h"
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
		using namespace std::chrono;
		using Framerate = duration<steady_clock::rep, std::ratio<1, 60>>;
		mNextFrame = steady_clock::now() + Framerate{ 1 };

		WM.Step();
		TM.Step();

		std::this_thread::sleep_until(mNextFrame);
		mNextFrame += Framerate{ 1 };
	}

	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
}
