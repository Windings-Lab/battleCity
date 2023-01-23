#include "PCHeader.h"
#include "Timer.h"

namespace BattleCity::Engine
{
	void Timer::Start(Seconds seconds, std::function<void()> onTimerEnd)
	{
		mDuration = std::chrono::seconds(seconds);
		mOnTimerEnd = std::move(onTimerEnd);
		mStartingTime = std::chrono::high_resolution_clock::now();
		mEnded = false;
	}

	void Timer::Update()
	{
		if(mEnded) return;

		auto endTime = std::chrono::high_resolution_clock::now();

		if(endTime - mStartingTime >= mDuration)
		{
			mOnTimerEnd();
			mEnded = true;
		}
	}
}

