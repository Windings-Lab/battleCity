#pragma once

namespace BattleCity::Engine
{
	using Seconds = int;
	using SecondsDuration = std::chrono::seconds;

	class Timer
	{
	public:
		Timer();
		virtual ~Timer() = default;

		virtual void StartOnce(Seconds, std::function<void()>);
		virtual void StartOnceRandom(Seconds, Seconds, std::function<void()>);

		virtual void Start(Seconds, std::function<void()>);
		void StartRandom(Seconds, Seconds, std::function<void()>);

		virtual void Repeat();
		void RepeatRandom(Seconds, Seconds);

		virtual void Update();

	protected:
		bool mStarted = false;
		bool mEnded = true;
		std::function<void()> mOnTimerEnd;

		std::chrono::high_resolution_clock::time_point mStartingTime;
		std::mt19937 mRandomGenerator;

	private:
		SecondsDuration mDuration;
	};
}


