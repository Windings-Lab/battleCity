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
#include "GameManager.h"
#include "Utility.h"
#include "Framework.h"
#include "Sprites.h"
#include "Wall.h"

#include <vector>
#include <iostream>
#include <fstream>

int battleCity::WorldManager::worldID = 1;
int battleCity::WorldManager::moveID = 1;

battleCity::WorldManager::WorldManager()
{
	setType("WorldManager");
	map = std::vector<std::vector<Object*>>(HEIGHT, std::vector<Object*>(WIDTH));
}

battleCity::WorldManager& battleCity::WorldManager::getInstance()
{
	static WorldManager single;
	return single;
}

int battleCity::WorldManager::startUp()
{
	//std::cout << "WorldManager - startUp" << std::endl;
	if(initMap() == 0);
	    return 0;
	return Manager::startUp();
}

void battleCity::WorldManager::shutDown()
{
	//std::cout << "WorldManager - shutDown" << std::endl;
	ObjectList listToDelete = worldList;
	ObjectListIterator it = ObjectListIterator(&listToDelete);
	for (it.first(); !it.isDone(); it.next())
	{
		delete *it.currentObject();
	}
	Manager::shutDown();
}

int battleCity::WorldManager::insertObject(Object* objectPtr)
{
	//std::cout << "WorldManager - insertObject" << std::endl;
	int check;
	if (objectPtr->getWorldMoveID() != 0)
	{
		moveID++;
		check = objectsToMove.insert(objectPtr);
		if (check == -1)
			return check;
	}
	worldID++;
	check = worldList.insert(objectPtr);
	objectPtr = NULL;
	return check;
}

int battleCity::WorldManager::removeObject(Object* objectPtr)
{
	//std::cout << "WorldManager - removeObject" << std::endl;
	int check;
	if (objectPtr->getWorldMoveID() != 0)
	{
		check = objectsToMove.removeByMoveID(objectPtr->getWorldMoveID());
		if (check == -1)
			return check;
	}
	check = worldList.removeByWorldID(objectPtr->getWorldID());
	objectPtr = NULL;
	return check;
}

battleCity::ObjectList battleCity::WorldManager::getAllObjects() const
{
	return worldList;
}

int battleCity::WorldManager::getSizeOfWorldList()
{
	return worldList.getSize();
}

int battleCity::WorldManager::getSizeOfMoveList()
{
	return objectsToMove.getSize();
}

int battleCity::WorldManager::getWorldID() const
{
	return worldID;
}

int battleCity::WorldManager::getMoveID() const
{
	return moveID;
}

std::vector<std::vector<battleCity::Object*>>& battleCity::WorldManager::getWorldMap()
{
	return map;
}

int battleCity::WorldManager::initMap()
{
	//std::cout << "WorldManager - initMap" << std::endl;
	char charToStore;
	std::ifstream mapFile(".\\data\\Maps\\level1.txt");
	if (!mapFile)
	{
		return 0;
	}

	for (int i = 0; i < HEIGHT; i++) {  // stop loops if nothing to read
		for (int j = 0; j < WIDTH; j++) {
			mapFile >> charToStore;
			if(charToStore - '0' == 1)
				map[i][j] = new Wall(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
		}
	}
	mapFile.close();

	return 1;
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
	//std::cout << "WorldManager - update" << std::endl;
	ObjectList listToIt = objectsToMove;
	ObjectListIterator it = ObjectListIterator(&objectsToMove);

	ObjectListIterator itUpdate = ObjectListIterator(&worldList);
	ObjectListIterator itDeletetion = ObjectListIterator(&deletionList);

	for (itUpdate.first(); !itUpdate.isDone(); itUpdate.next())
	{
		(*itUpdate.currentObject())->update();
	}

	for (it.first(); !it.isDone(); it.next())
	{
		Vector newPos = (*it.currentObject())->predictPosition();
		moveObject(*it.currentObject(), newPos);
	}

	for (itDeletetion.first(); !itDeletetion.isDone(); itDeletetion.next())
	{
		Object* objToDelete = *itDeletetion.currentObject();
		if (objToDelete->getType() == "Wall")
		{
			Vector pos = objToDelete->getPosition();
			int x = (pos.x - SCR.getBoundaryL()) / 16;
			int y = (pos.y - SCR.getBoundaryU()) / 16;
			map[y][x] = NULL;
		}
		delete objToDelete;
		objToDelete = NULL;
	}

	deletionList.clear();
}

void battleCity::WorldManager::draw()
{
	ObjectListIterator it = ObjectListIterator(&worldList);

	drawBackground();

	for (it.first(); !it.isDone(); it.next())
	{
		(*it.currentObject())->draw();
	}
}

void battleCity::WorldManager::drawBackground()
{

	drawSprite(&SPR.getBackgroundSprite(), SCR.getBoundaryL(), SCR.getBoundaryU());
}

int battleCity::WorldManager::moveObject(Object* ptrObject, Vector where)
{
	//std::cout << "moveObject" << std::endl;
	if (ptrObject->isSolid() || ptrObject->isSoft())
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
				EventCollision collision(ptrObject, tempObject, where);

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

	objectPtr->setHealth(-1);

	if (objectPtr->getHealth() == 0)
	{
		deletionList.insert(objectPtr);
	}
	objectPtr = NULL;
	return 0;
}

battleCity::ObjectList battleCity::WorldManager::getCollisions(const Object* ptrObject, Vector where) const
{
	ObjectList collisionList;
	if (ptrObject->getSpeed() == 0)
	{
		ptrObject = NULL;
		return collisionList;
	}
	ObjectListIterator it = ObjectListIterator(&objectsToMove);
	Object* tempObject = NULL;
	Vector objWorldIndex = ptrObject->getWorldIndex();

	tempObject = map[(int)objWorldIndex.y][(int)objWorldIndex.x];
	auto iterateFullListFunc =
	[&it, &ptrObject, &collisionList, &where]()
	{
		for (it.first(); !it.isDone(); it.next())
		{
			Object* tempObject = *it.currentObject();
			if (tempObject == ptrObject)
			{
				continue;
			}
			Box b = getWorldBox(ptrObject, where);
			Box bTemp = getWorldBox(tempObject);
			if (boxesIntersect(b, bTemp) &&
			   (tempObject->isSolid() || tempObject->isSoft()))
			{
				collisionList.insert(tempObject);
			}
		}
	};
	// IF NULL then check for other movable objects
	if (tempObject == NULL)
	{
		//std::cout << "WorldManager - getCollisions - 393" << std::endl;
		iterateFullListFunc();
		/*std::cout << "WorldManager - getCollisions - 395" << std::endl;*/
	}
	// Else we are checking this wall for collision
	else
	{
		Box b = getWorldBox(ptrObject, where);
		Box bTemp = getWorldBox(tempObject);
		// If false, then check other objects for collision
		// for example Player(14, 0), Wall(15, 0) no collision
		if (boxesIntersect(b, bTemp) &&
			(tempObject->isSolid() || tempObject->isSoft()))
		{
			collisionList.insert(tempObject);
		}
		// Check other movable objects
		else
		{
			iterateFullListFunc();
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