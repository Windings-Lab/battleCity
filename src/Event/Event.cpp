#include "PCHeader.h"
#include "Event.h"


namespace BattleCity
{
	Event::Event() : mEventType(EventEnum::Type::Event) {}

	void Event::SetType(EventEnum::Type newType)
	{
		mEventType = newType;
	}

	EventEnum::Type Event::GetType() const
	{
		return mEventType;
	}
}
