#include "Manager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "Explosion.h"
#include "ObjectListIterator.h"

#include <iostream>
#include <vector>

battleCity::Manager::Manager() : _type(ManagerType::Manager), _started(false) {}

battleCity::Manager::~Manager()
{
#if DEBUG == 2
	std::cout << "Manager Destructor" << std::endl;
#endif
}

void battleCity::Manager::SetType(ManagerType newType)
{
	_type = newType;
}

battleCity::ManagerType battleCity::Manager::GetType() const
{
	return _type;
}

int battleCity::Manager::StartUp()
{
	_started = true;
	return 0;
}

void battleCity::Manager::ShutDown()
{
	_started = false;
}

bool battleCity::Manager::IsStarted() const
{
	return _started;
}

int battleCity::Manager::OnEvent(const Event* ptrEvent) const
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

	ptrEvent = nullptr;
	return count;
}
