#include "Event.h"


BattleCity::Event::Event() : mEventType(EventType::Event) {}

void BattleCity::Event::SetType(EventType newType)
{
	mEventType = newType;
}

BattleCity::EventType BattleCity::Event::GetType() const
{
	return mEventType;
}