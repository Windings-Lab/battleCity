#include "Manager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "ObjectList.h"
#include "Object.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "Screen.h"
#include "Box.h"
#include "Utility.h"

#include <vector>
#include <iostream>


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

battleCity::ObjectList battleCity::WorldManager::objectsOfType(std::string type)
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

	for (it.first(); !it.isDone(); it.next())
	{
		(*it.currentObject())->update();
	}

	for (it.first(); !it.isDone(); it.next())
	{
		Vector newPos = (*it.currentObject())->predictPosition();
		moveObject(*it.currentObject(), newPos);
	}

	for (itDeletetion.first(); !itDeletetion.isDone(); itDeletetion.next())
	{
		Object* objToDelete = *itDeletetion.currentObject();
		delete objToDelete;
		objToDelete = NULL;
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
	if (ptrObject->isSolid())
	{
		ObjectList newList = getCollisions(ptrObject, where);

		if (!newList.isEmpty())
		{
			bool doMove = true;
			ObjectListIterator it = ObjectListIterator(&newList);
			Object* tempObject = NULL;

			for (it.first(); !it.isDone(); it.next())
			{
				tempObject = *it.currentObject();
				EventCollision collision = EventCollision(ptrObject, tempObject, where);

				ptrObject->eventHandler(&collision);
				tempObject->eventHandler(&collision);

				if (ptrObject->isSolid() && tempObject->isSolid())
					doMove = false;
			}
			tempObject = NULL;

			if (!doMove)
			{
				ptrObject = NULL;
				return -1;
			}
		}
	}
	int i = 0;
	if ((where.x >= SCR.getBoundaryL() && where.x + ptrObject->getSpriteX() <= SCR.getBoundaryR()) &&
		(where.y >= SCR.getBoundaryU() && where.y + ptrObject->getSpriteY() <= SCR.getBoundaryD()))
	{
		i = ptrObject->setPosition(where);
	}
	else
	{
		ptrObject->eventHandler(&EventOut());
	}

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

battleCity::ObjectList battleCity::WorldManager::getCollisions(const Object* ptrObject, Vector where) const
{
	ObjectList collisionList;
	ObjectListIterator it = ObjectListIterator(&worldList);
	Object* tempObject = NULL;

	for (it.first(); !it.isDone(); it.next())
	{
		Object* tempObject = *it.currentObject();
		Box b = getWorldBox(ptrObject, where);
		Box bTemp = getWorldBox(tempObject);
		if (tempObject != ptrObject)
		{
			if (boxesIntersect(b, bTemp) &&
				tempObject->isSolid())
			{
				collisionList.insert(tempObject);
			}
		}
	}

	tempObject = NULL;
	ptrObject = NULL;
	return collisionList;
}

battleCity::WorldManager::~WorldManager()
{
#if DEBUG == 2
	std::cout << "WorldManager Destructor" << std::endl;
	std::cout << std::endl;
#endif
}