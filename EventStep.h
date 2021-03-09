#pragma once
#include "Event.h"

namespace battleCity
{
	const string STEP_EVENT = "Step";

	class EventStep : public Event
	{
	private:
		/// Iteration number of game loop
		unsigned int stepCount;  

	public:
		/// Default constructor.
		EventStep();
		~EventStep();

		/// Constructor with initial step count.
		EventStep(unsigned int init);

		/// Set step count.
		void setStepCount(unsigned int newStep);

		/// Get step count.
		int getStepCount() const;
	};
}

