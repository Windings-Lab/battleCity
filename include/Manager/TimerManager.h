#pragma once

#include "Manager.h"
#include "TimerHandle.h"

namespace BattleCity::Manager
{
	class TimerManager final : public Manager
	{
		using TimerFuncPair = std::pair<std::unique_ptr<TimerHandle>, std::function<void()>>;
	public:
		static TimerManager& GetInstance();

		TimerManager(const TimerManager&) = delete;
		TimerManager(TimerManager&&) = delete;

		TimerManager& operator=(const TimerManager&) = delete;
		TimerManager& operator=(TimerManager&&) = delete;

		~TimerManager() override = default;
	public:
		void StartUp() override;
		void ShutDown() override;

		void Step();

		void SetTimer(std::function<void()>&& onTimerEndFunc, long long durationInSec);
		void SetTimer(std::function<void()>&& onTimerEndFunc, std::string_view timerName, long long durationInSec);

	private:
		TimerManager();

		std::vector<TimerFuncPair> mTimerList;
	};

	constexpr auto& TM = TimerManager::GetInstance;
}

