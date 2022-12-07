#pragma once

#include "Manager.h"
#include "TFunction.h"
#include "TimerHandle.h"

namespace BattleCity::Manager
{
	class TimerManager final : public Manager
	{
	public:
		TimerManager(const TimerManager&) = delete;
		TimerManager(TimerManager&&) = delete;

		TimerManager& operator=(const TimerManager&) = delete;
		TimerManager& operator=(TimerManager&&) = delete;

		~TimerManager() override = default;
	public:
		void StartUp() override;
		void ShutDown() override;

		void Step();

		template <typename FuncType, typename... ArgTypes>
		void SetTimer(TFunction<FuncType, ArgTypes&...> onTimerEndFunc, int durationInSec);

	private:
		TimerManager();

		std::vector<TimerHandle> mTimerList;
	};
}

