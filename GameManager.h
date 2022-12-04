#pragma once

#include "Manager.h"

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

	public:
		void StartUp() override;
		void ShutDown() override;

		void Step();

		void SetGameOverState();
		bool GetGameOverState() const;

		bool GetGameOver() const;
	private:
		// Singleton
		GameManager();

		bool mGameOver;
		bool mGameOverState;
	};

	inline GameManager& GM = GameManager::GetInstance();
}
