#include "Manager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "Explosion.h"
#include "ObjectListIterator.h"

#include <iostream>
#include <vector>

battleCity::Manager::Manager() : type(""), started(false) {}

battleCity::Manager::~Manager()
{
#if DEBUG == 2
	std::cout << "Manager Destructor" << std::endl;
#endif
}

void battleCity::Manager::setType(std::string newType)
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

int battleCity::Manager::onEvent(const Event* ptrEvent) const
{
	int count = 0;
	ObjectList listToIt = WM.objectsToMove;
	ObjectList explosion = WM.objectsOfType("Explosion");
	ObjectListIterator itEvent = ObjectListIterator(&listToIt);
	ObjectListIterator itEventExplosion = ObjectListIterator(&explosion);

	for (itEvent.first(); !itEvent.isDone(); itEvent.next())
	{
		(*itEvent.currentObject())->eventHandler(ptrEvent);
		count++;
	}

	for (itEventExplosion.first(); !itEventExplosion.isDone(); itEventExplosion.next())
	{
		(*itEventExplosion.currentObject())->eventHandler(ptrEvent);
		count++;
	}

	ptrEvent = NULL;
	return count;
}
