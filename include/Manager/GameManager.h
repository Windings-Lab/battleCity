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
	private:
		// Singleton
		GameManager();

		bool mGameOver;

	};

	inline GameManager& GM = GameManager::GetInstance();
}
