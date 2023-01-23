#include "PCHeader.h"
#include "TimerMilliseconds.h"

namespace BattleCity::Engine
{
	TimerMilliseconds::TimerMilliseconds()
		: Timer()
		, mDuration(std::chrono::milliseconds(0))
	{
	}

	void TimerMilliseconds::StartOnceRandom(Milliseconds min, Milliseconds max, std::function<void()> onTimerEnd)
	{
		if (mStarted) return;

		std::uniform_int_distribution dist(min, max);
		int randomSeconds = dist(mRandomGenerator);

		mDuration = std::chrono::milliseconds(randomSeconds);
		mOnTimerEnd = std::move(onTimerEnd);
		mStartingTime = std::chrono::high_resolution_clock::now();
		mEnded = false;
		mStarted = true;
	}

	void TimerMilliseconds::StartOnce(Milliseconds mili, std::function<void()> onTimerEnd)
	{
		if (mStarted) return;

		mDuration = std::chrono::milliseconds(mili);
		mOnTimerEnd = std::move(onTimerEnd);
		mStartingTime = std::chrono::high_resolution_clock::now();
		mEnded = false;
		mStarted = true;
	}

	void TimerMilliseconds::Start(Milliseconds mili, std::function<void()> onTimerEnd)
	{
		mDuration = std::chrono::milliseconds(mili);
		mOnTimerEnd = std::move(onTimerEnd);
		mStartingTime = std::chrono::high_resolution_clock::now();
		mEnded = false;
	}

	void TimerMilliseconds::Update()
	{
		if (mEnded) return;

		auto endTime = std::chrono::high_resolution_clock::now();

		if (endTime - mStartingTime >= mDuration)
		{
			mOnTimerEnd();
			mEnded = true;
			mStarted = false;
		}
	}

	void TimerMilliseconds::Repeat()
	{
		auto endTime = std::chrono::high_resolution_clock::now();

		if (endTime - mStartingTime >= mDuration)
		{
			mOnTimerEnd();
			mStartingTime = std::chrono::high_resolution_clock::now();
		}
	}
}
