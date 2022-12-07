#include "PCHeader.h"
#include "TimerManager.h"

namespace BattleCity::Manager
{
	void TimerManager::StartUp()
	{
	}

	void TimerManager::ShutDown()
	{
	}

	template<typename FuncType, typename ...ArgTypes>
	void TimerManager::SetTimer(TFunction<FuncType, ArgTypes&...> onTimerEndFunc, int durationInSec)
	{
	}

	void TimerManager::Step()
	{
		for (auto& timer : mTimerList)
		{
			
		}
	}
}

