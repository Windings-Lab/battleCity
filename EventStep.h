#pragma once
#include "Event.h"

namespace battleCity
{
	class EventStep : public Event
	{
	private:
		/// Iteration number of game loop
		int stepCount;  

	public:
		/// Default constructor.
		EventStep();
		~EventStep();

		/// Constructor with initial step count.
		EventStep(int init);

		/// Set step count.
		void setStepCount(int newStep);

		/// Get step count.
		int getStepCount() const;
	};
}

