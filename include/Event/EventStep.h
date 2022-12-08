#pragma once

#include "Event.h"

namespace BattleCity::Event
{
	class EventStep final : public Event
	{
	public:
		EventStep();

		EventStep(const EventStep&) = default;
		EventStep(EventStep&&) = default;

		EventStep& operator=(const EventStep&) = default;
		EventStep& operator=(EventStep&&) = default;

		~EventStep() override = default;

		int GetStepCount() const;
	private:
		/// Iteration number of game loop
		unsigned int mStepCount;
	};
}
