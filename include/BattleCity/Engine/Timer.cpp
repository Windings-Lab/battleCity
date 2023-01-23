#include "PCHeader.h"
#include "Timer.h"

namespace BattleCity::Engine
{
	Timer::Timer()
		: mDuration(std::chrono::seconds(0))
		, mRandomGenerator(std::random_device{}())
	{
	}

	void Timer::Start(Seconds seconds, std::function<void()> onTimerEnd)
	{
		mDuration = std::chrono::seconds(seconds);
		mOnTimerEnd = std::move(onTimerEnd);
		mStartingTime = std::chrono::high_resolution_clock::now();
		mEnded = false;
	}

	void Timer::StartRandom(Seconds min, Seconds max, std::function<void()> onTimerEnd)
	{
		std::uniform_int_distribution dist(min, max);
		int randomSeconds = dist(mRandomGenerator);

		mDuration = std::chrono::seconds(randomSeconds);
		mOnTimerEnd = std::move(onTimerEnd);
		mStartingTime = std::chrono::high_resolution_clock::now();
		mEnded = false;
	}

	void Timer::Repeat()
	{
		auto endTime = std::chrono::high_resolution_clock::now();

		if (endTime - mStartingTime >= mDuration)
		{
			mOnTimerEnd();
			mStartingTime = std::chrono::high_resolution_clock::now();
		}
	}

	void Timer::RepeatRandom(Seconds min, Seconds max)
	{
		auto endTime = std::chrono::high_resolution_clock::now();

		if (endTime - mStartingTime >= mDuration)
		{
			mOnTimerEnd();
			mStartingTime = std::chrono::high_resolution_clock::now();
			std::uniform_int_distribution dist(min, max);
			int randomSeconds = dist(mRandomGenerator);

			mDuration = std::chrono::seconds(randomSeconds);
		}
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

