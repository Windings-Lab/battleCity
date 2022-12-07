#include "PCHeader.h"
#include "TimerHandle.h"

namespace BattleCity
{
	TimerHandle::TimerHandle() : TimerHandle(0)
	{
		
	}

	TimerHandle::TimerHandle(int duration) : mRunning(false), mDuration(duration)
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
		std::chrono::time_point<std::chrono::system_clock> endTime;

		if (mRunning)
		{
			endTime = std::chrono::system_clock::now();
		}
		else
		{
			endTime = mEndTime;
		}

		if(std::chrono::duration_cast<std::chrono::seconds>(endTime - mStartTime).count() <= mDuration)
		{
			return false;
		}

		Stop();
		return true;
	}


}
