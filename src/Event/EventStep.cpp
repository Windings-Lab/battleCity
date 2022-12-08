#include "PCHeader.h"
#include "EventStep.h"

namespace BattleCity::Event
{
	EventStep::EventStep() : mStepCount()
	{
		SetType(Type::Step);
	}

	int EventStep::GetStepCount() const
	{
		return mStepCount;
	}
}
