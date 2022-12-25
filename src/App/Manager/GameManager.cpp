#include "PCHeader.h"

#include "GameManager.h"

#include "BCSprite.h"
#include "SpritePathManager.h"
#include "WorldManager.h"

#include "Object.h"

namespace BattleCity::Manager
{
	GameManager::GameManager() : Manager(), mGameOver(false) {}

	GameManager& GameManager::GetInstance()
	{
		static GameManager single;
		return single;
	}

	void GameManager::StartUp()
	{
		PM().StartUp();
		WM().StartUp();
	}
	void GameManager::ShutDown()
	{
		WM().ShutDown();
		PM().ShutDown();
	}

	void GameManager::Step()
	{
		using namespace std::chrono;
		using Framerate = duration<steady_clock::rep, std::ratio<1, 60>>;
		mNextFrame = steady_clock::now() + Framerate{ 1 };

		Update();
		// Resolve Collisions
		// Delete All
		Draw();

		std::this_thread::sleep_until(mNextFrame);
		mNextFrame += Framerate{ 1 };
	}

	void GameManager::Update()
	{
		for (auto& [id, obj] : WM().GetFrontLayerIterator())
		{
			obj->Update();
		}
	}

	void GameManager::Draw()
	{
		for (auto& [id, obj] : WM().GetBackLayerIterator())
		{
			obj->Draw();
		}

		for (auto& [id, obj] : WM().GetFrontLayerIterator())
		{
			obj->Draw();
		}
	}

	bool GameManager::GetGameOver() const
	{
		return mGameOver;
	}
}
