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
		using namespace std::chrono;
		using Framerate = duration<steady_clock::rep, std::ratio<1, 60>>;
		auto next = steady_clock::now() + Framerate{ 1 };
		WM.Step();
	}

	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
}
