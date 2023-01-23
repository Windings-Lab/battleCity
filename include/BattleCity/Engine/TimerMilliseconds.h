#pragma once

#include "Timer.h"

namespace BattleCity::Engine
{
	using Milliseconds = int;
	using MillisecondsDuration = std::chrono::milliseconds;

	class TimerMilliseconds : public Timer
	{
	public:
		TimerMilliseconds();

		void StartOnce(Seconds, std::function<void()>) override;
		void Start(Milliseconds, std::function<void()>) override;
		void Update() override;
		void Repeat() override;

	private:
		MillisecondsDuration mDuration;
	};
}
