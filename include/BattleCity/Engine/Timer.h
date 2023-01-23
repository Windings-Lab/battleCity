#pragma once

namespace BattleCity::Engine
{
	using Seconds = int;
	using Duration = std::chrono::seconds;

	class Timer
	{
	public:
		Timer() = default;

		void Start(Seconds, std::function<void()>);

		void Repeat();
		void Update();

	private:
		bool mEnded = true;
		std::function<void()> mOnTimerEnd;
		
		Duration mDuration = std::chrono::seconds(0);
		std::chrono::high_resolution_clock::time_point mStartingTime;
	};
}


