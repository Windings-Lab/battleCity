#pragma once

namespace BattleCity::Engine
{
	using Seconds = int;
	using Duration = std::chrono::seconds;

	class Timer
	{
	public:
		Timer();

		void Start(Seconds, std::function<void()>);
		void StartRandom(Seconds, Seconds, std::function<void()>);

		void Repeat();
		void RepeatRandom(Seconds, Seconds);

		void Update();

	private:
		bool mEnded = true;
		std::function<void()> mOnTimerEnd;
		
		Duration mDuration;
		std::chrono::high_resolution_clock::time_point mStartingTime;

		std::mt19937 mRandomGenerator;
	};
}


