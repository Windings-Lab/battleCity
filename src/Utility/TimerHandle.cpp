#include "PCHeader.h"
#include "TimerHandle.h"

namespace BattleCity
{
	using namespace std::string_view_literals;

	TimerHandle::TimerHandle() : TimerHandle(0) {}
	TimerHandle::TimerHandle(int duration) : TimerHandle(""sv, duration) {}
	TimerHandle::TimerHandle(std::string_view timerName, int duration)
		: mTimerName(timerName), mDuration(duration), mRunning(false)
	{
	}

	void TimerHandle::Start()
	{
		mStartTime = std::chrono::system_clock::now();
		mRunning = true;
	}

	void TimerHandle::Stop()
	{
		mEndTime = std::chrono::system_clock::now();
		mRunning = false;
	}

	bool TimerHandle::HasEnded()
	{
		if (GetSeconds() <= mDuration)
		{
			return false;
		}

		Stop();
		return true;
	}

	long long TimerHandle::GetSeconds()
	{
		std::chrono::time_point<std::chrono::system_clock> endTime;

		if (mRunning)
		{
			endTime = std::chrono::system_clock::now();
		}
		else
		{
			endTime = mEndTime;
		}

		return std::chrono::duration_cast<std::chrono::seconds>(endTime - mStartTime).count();
	}

	std::string_view TimerHandle::GetName() const
	{
		return mTimerName;
	}


}
