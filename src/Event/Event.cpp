#include "PCHeader.h"
#include "Event.h"


namespace BattleCity::Event
{
	Event::Event() : mEventType(Type::Event) {}

	void Event::SetType(Type newType)
	{
		mEventType = newType;
	}

	Type Event::GetType() const
	{
		return mEventType;
	}
}
