#include "Event.h"


battleCity::Event::Event() : mEventType(EventType::Event) {}

void battleCity::Event::SetType(EventType newType)
{
	mEventType = newType;
}

battleCity::EventType battleCity::Event::GetType() const
{
	return mEventType;
}