#include "PCHeader.h"
#include "TimerManager.h"

namespace BattleCity::Manager
{
	TimerManager& TimerManager::GetInstance()
	{
		static TimerManager timerManager;
		return timerManager;
	}

	TimerManager::TimerManager() : Manager(Type::Timer)
	{
		
	}

	void TimerManager::StartUp()
	{
	}

	void TimerManager::ShutDown()
	{
	}

	void TimerManager::SetTimer(std::function<void()>&& onTimerEndFunc, long long durationInSec)
	{
		SetTimer(std::move(onTimerEndFunc), "NoName"sv, durationInSec);
	}

	void TimerManager::SetTimer(std::function<void()>&& onTimerEndFunc, std::string_view timerName, long long durationInSec)
	{
		auto newTimer = std::make_unique<TimerHandle>(timerName, durationInSec);
		newTimer->Start();
		auto pair = std::make_pair(std::move(newTimer), std::move(onTimerEndFunc));

		mTimerList.push_back(std::move(pair));
	}

	void TimerManager::Step()
	{
		auto filterLambda = [](const TimerFuncPair& pair)
		{
			if (!pair.first->HasEnded())
			{
#ifdef _DEBUG
				std::cout << pair.first->GetName() << ": " << pair.first->GetSeconds() << std::endl;
#endif
				return false;
			}

			pair.second();
			return true;
		};

		std::vector<TimerFuncPair>::const_iterator filtered
			= std::remove_if(
				mTimerList.begin(),
				mTimerList.end(),
				filterLambda);

		mTimerList.erase(mTimerList.begin(), std::move(filtered));
	}
}

