#include "Manager.h"

battleCity::Manager::Manager() : type(""), started(false) {}

battleCity::Manager::~Manager()
{
#if DEBUG == 2
	std::cout << "Manager Destructor" << std::endl;
#endif
}

void battleCity::Manager::setType(string newType)
{
	type = newType;
}

std::string battleCity::Manager::getType() const
{
	return type;
}

int battleCity::Manager::startUp()
{
	started = true;
	return 0;
}

void battleCity::Manager::shutDown()
{
	started = false;
}

bool battleCity::Manager::isStarted() const
{
	return started;
}
