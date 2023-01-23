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

		void Start(Milliseconds, std::function<void()>);
		void Update() override;
		void Repeat() override;

	private:
		MillisecondsDuration mDuration;
	};
}
