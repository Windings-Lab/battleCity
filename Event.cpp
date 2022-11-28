#include "Event.h"


battleCity::Event::Event() : _eventType(EventType::Event) {}

void battleCity::Event::SetType(EventType newType)
{
	_eventType = newType;
}

battleCity::EventType battleCity::Event::GetType() const
{
	return _eventType;
}

battleCity::Event::~Event()
{
//#if DEBUG == 2
//	std::cout << "Event Destructor" << std::endl;
//#endif
}