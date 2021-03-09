#include "WorldManager.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "EventStep.h"

battleCity::WorldManager::WorldManager()
{
	setType("WorldManager");
}

battleCity::WorldManager& battleCity::WorldManager::getInstance()
{
	static WorldManager single;
	return single;
}

int battleCity::WorldManager::startUp()
{
	return Manager::startUp();
}

void battleCity::WorldManager::shutDown()
{
	ObjectList all = worldList;
	ObjectListIterator it = ObjectListIterator(&all);
	for (it.first(); !it.isDone(); it.next())
	{
		delete *it.currentObject();
	}
	Manager::shutDown();
}

int battleCity::WorldManager::insertObject(Object* objectPtr)
{
	int i = worldList.insert(objectPtr);
	objectPtr = NULL;
	return i;
}

int battleCity::WorldManager::removeObject(Object* objectPtr)
{
	int i = worldList.remove(objectPtr);
	objectPtr = NULL;
	return i;
}

battleCity::ObjectList battleCity::WorldManager::getAllObjects() const
{
	return worldList;
}

battleCity::ObjectList battleCity::WorldManager::objectsOfType(string type)
{
	ObjectList newList = worldList;
	ObjectListIterator it = ObjectListIterator(&worldList);

	for (it.first(); !it.isDone(); it.next())
	{
		if ((*it.currentObject())->getType() == type)
			newList.insert(*it.currentObject());
	}

	return newList;
}

void battleCity::WorldManager::update()
{
	ObjectListIterator it = ObjectListIterator(&worldList);
	ObjectListIterator itDeletetion = ObjectListIterator(&deletionList);
	ObjectListIterator itPlayer = ObjectListIterator(&worldList);
	itPlayer.first();
	Vector newPos = (*itPlayer.currentObject())->predictPosition();

	for (it.first(); !it.isDone(); it.next())
	{
		(*it.currentObject())->update();
	}

	if ((newPos.x >= 0 && newPos.x + 32 <= Screen::width) &&
		(newPos.y >= 0 && newPos.y + 32 <= Screen::height))
	{
		moveObject(*itPlayer.currentObject(), newPos);
	}

	for (itDeletetion.first(); !itDeletetion.isDone(); itDeletetion.next())
	{
		delete *itDeletetion.currentObject();
	}
	deletionList.clear();
}

void battleCity::WorldManager::draw()
{
	ObjectListIterator it = ObjectListIterator(&worldList);

	for (it.first(); !it.isDone(); it.next())
	{
		(*it.currentObject())->draw();
	}
}

int battleCity::WorldManager::moveObject(Object* ptrObject, Vector where)
{
	int i = ptrObject->setPosition(where);
	ptrObject = NULL;
	return i;
}

int battleCity::WorldManager::markForDelete(Object* objectPtr)
{
	ObjectListIterator it = ObjectListIterator(&deletionList);

	for (it.first(); !it.isDone(); it.next())
	{
		if (*it.currentObject() == objectPtr)
			return 0;
	}

	deletionList.insert(objectPtr);
	objectPtr = NULL;
	return 0;
}

battleCity::WorldManager::~WorldManager()
{
#if DEBUG == 2
	std::cout << "WorldManager Destructor" << std::endl;
	cout << endl;
#endif
}