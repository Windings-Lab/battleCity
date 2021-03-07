#include "Event.h"

battleCity::Event::Event() : eventType("Event") {}

void battleCity::Event::setType(std::string newType)
{
	eventType = newType;
}

string battleCity::Event::getType() const
{
	return eventType;
}

battleCity::Event::~Event()
{
#if DEBUG == 2
	std::cout << "Event Destructor" << std::endl;
#endif
}