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

		void Start(Seconds, std::function<void()>);
		void StartRandom(Seconds, Seconds, std::function<void()>);

		virtual void Repeat();
		void RepeatRandom(Seconds, Seconds);

		virtual void Update();

	protected:
		bool mEnded = true;
		std::function<void()> mOnTimerEnd;

		std::chrono::high_resolution_clock::time_point mStartingTime;
		std::mt19937 mRandomGenerator;

	private:
		SecondsDuration mDuration;
	};
}


