#include "EventStep.h"
#include "GameManager.h"

namespace BattleCity
{
	EventStep::EventStep() : mStepCount()
	{
		SetType(EventType::Step);
	}

	int EventStep::GetStepCount() const
	{
		return mStepCount;
	}
}
