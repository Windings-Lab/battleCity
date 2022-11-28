#include "Event.h"


battleCity::Event::Event() : eventType(EventType::Event) {}

void battleCity::Event::setType(EventType newType)
{
	eventType = newType;
}

battleCity::EventType battleCity::Event::getType() const
{
	return eventType;
}

battleCity::Event::~Event()
{
//#if DEBUG == 2
//	std::cout << "Event Destructor" << std::endl;
//#endif
}