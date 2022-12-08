#include "PCHeader.h"

#include "GameManager.h"

#include "MapManager.h"
#include "SpriteManager.h"
#include "SpritePathManager.h"
#include "TimerManager.h"
#include "WorldManager.h"

namespace BattleCity::Manager
{
	GameManager::GameManager() : Manager(Type::Game), mGameOver(false) {}

	GameManager& GameManager::GetInstance()
	{
		static GameManager single;
		return single;
	}

	void GameManager::StartUp()
	{
		TM.StartUp();
		PM.StartUp();
		SM.StartUp();
		MAP.StartUp();
		WM.StartUp();
	}
	void GameManager::ShutDown()
	{
		WM.ShutDown();
		MAP.ShutDown();
		SM.ShutDown();
		PM.ShutDown();
		TM.ShutDown();
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
