#pragma once

#include "Clock.h"
#include "Manager.h"

const int FRAME_TIME_DEFAULT = 16;

namespace battleCity
{
	class GameManager final : Manager
	{
	public:
		// Singleton
		static GameManager& GetInstance();

		GameManager(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;

		void operator=(const GameManager&) = delete;
		void operator=(GameManager&&) = delete;

		~GameManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		void Update();

		void SetGameOverState();
		bool GetGameOverState() const;

		bool GetGameOver() const;

		int GetStepCount() const;

		void SetCustomStepCount(int stepCount);
		int GetCustomStepCount() const;

		int SpriteInit();
		bool GameOverTimerEnded();
	private:
		// Singleton
		GameManager();

		bool mGameOver;
		bool mGameOverState;
		// Clock management
		Clock mClock;
		// Target time per game loop, in seconds
		int mFrameTime;
		// Count of game loop iterations
		int mStepCount;
		int mCustomStepCount;
	};

	inline GameManager& GM = GameManager::GetInstance();
}
