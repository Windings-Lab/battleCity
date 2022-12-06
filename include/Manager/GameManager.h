#pragma once

#include "Manager.h"

namespace BattleCity::Manager
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

	public:
		void StartUp() override;
		void ShutDown() override;
	public:
		void Step();

		bool GetGameOver() const;

		const float& GetTime();
	private:
		// Singleton
		GameManager();

		bool mGameOver;
		double mTime = 0.0f;
		float mDeltaTime = 1.0f / 60.f;
	};

	inline GameManager& GM = GameManager::GetInstance();
}
