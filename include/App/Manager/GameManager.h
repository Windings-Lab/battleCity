#pragma once

#include "Manager.h"

namespace BattleCity::Manager
{
	class GameManager final : Manager
	{
	private:
		GameManager();

	public:
		static GameManager& GetInstance();

		GameManager(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;

		void operator=(const GameManager&) = delete;
		void operator=(GameManager&&) = delete;

		~GameManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		void Step();

		bool GetGameOver() const;
	private:
		void Update();
		void Draw();

	private:
		bool mGameOver;

		std::chrono::time_point <std::chrono::steady_clock,
			std::common_type_t<std::chrono::duration<long long, std::ratio<1, 1000000000>>,
			std::chrono::duration<long long, std::ratio<1, 60>>>> mNextFrame;
	};

	constexpr auto& GM = GameManager::GetInstance;
}
