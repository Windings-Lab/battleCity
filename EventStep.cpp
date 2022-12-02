#include "EventStep.h"
#include "GameManager.h"

namespace battleCity
{
	EventStep::EventStep() : mStepCount(GM.stepCount)
	{
		SetType(EventType::Step);
	}

	int EventStep::GetStepCount() const
	{
		return mStepCount;
	}
}
