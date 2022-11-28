#include "Manager.h"
#include "WorldManager.h"
#include "ObjectListIterator.h"
#include "ObjectList.h"
#include "Object.h"
#include "Vector.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "Screen.h"
#include "PhoenixAndFlag.h"
#include "Box.h"
#include "GameManager.h"
#include "PowerUp.h"
#include "Utility.h"
#include "Framework.h"
#include "Tank.h"
#include "Sprites.h"
#include "Wall.h"
#include "PowerUp.h"

#include <vector>
#include <iostream>
#include <fstream>

using namespace std::string_view_literals;

int battleCity::WorldManager::worldID = 1;
int battleCity::WorldManager::moveID = 1;

battleCity::WorldManager::WorldManager()
{
	SetType("WorldManager");
	map = std::vector<std::vector<Object*>>(HEIGHT, std::vector<Object*>(WIDTH));
	powerUpPositions = std::vector<std::vector<int>>(0, std::vector<int>(0));

	gameOverPos.x = 290;
	gameOverPos.y = 600;
	gameOver = false;

	tankCount = 0;
	killCount = 0;
	tankStorage = 20;

	powerUp = nullptr;
	isPowerUp = false;
	powerUpisTaked = false;
}

battleCity::WorldManager& battleCity::WorldManager::getInstance()
{
	static WorldManager single;
	return single;
}

int battleCity::WorldManager::startUp(TankPlayer& newPlayer)
{
	//std::cout << "WorldManager - startUp" << std::endl;
	if(initMap(newPlayer) == 0)
	    return 0;
	gameOverSpr = &SPR.getGameOverSprite();
	return Manager::StartUp();
}

void battleCity::WorldManager::ShutDown()
{
	//std::cout << "WorldManager - shutDown" << std::endl;
	ObjectList listToDelete = worldList;
	ObjectListIterator it = ObjectListIterator(&listToDelete);
	for (it.first(); !it.isDone(); it.next())
	{
		delete *it.currentObject();
	}
	Manager::ShutDown();
}

void battleCity::WorldManager::setGameOverState()
{
	if (gameOver)
		return;
	GM.setStepCount(1);
	GM.setPlayerHealthToZero();
	gameOver = true;
}

void battleCity::WorldManager::setTankCount(int newTankCount)
{
	tankCount += newTankCount;
}

int battleCity::WorldManager::getTankCount()
{
	return tankCount;
}

void battleCity::WorldManager::setKillCount(int newKillCount)
{
	killCount += newKillCount;
}

int battleCity::WorldManager::getKillCount()
{
	return killCount;
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
	objectPtr = nullptr;
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
	objectPtr = nullptr;
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

std::vector<std::vector<int>>& battleCity::WorldManager::getPowerUpPositions()
{
	return powerUpPositions;
}

void battleCity::WorldManager::createSomeTanks()
{
	int rnd = randomNumber(0, 1);
	if (GM.stepCount % 450 == 0 && tankCount != 6 && tankStorage > 0)
	{
		if (rnd == 1)
			new Tank(500, 45);
		else
			new Tank(275, 45);
	}
}

int battleCity::WorldManager::initMap(TankPlayer& newPlayer)
{
	//std::cout << "WorldManager - initMap" << std::endl;
	char charToStore;
	std::ifstream mapFile(".\\data\\Maps\\level1.txt");
	if (!mapFile)
	{
		std::cout << "Map not found" << std::endl;
		exit(0);
	}

	int powerUpY = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			mapFile >> charToStore;
			if (charToStore - '0' == 4)
				map[i][j] = new Wall(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
			else if (charToStore - '0' == 1)
				newPlayer.setPosition(Vector(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i)));
			else if (charToStore - '0' == 2)
				new Tank(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
			else if (charToStore - '0' == 5)
				new PhoenixAndFlag(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
			else if (charToStore - '0' == 7)
			{
				powerUpPositions.push_back(std::vector<int>());
				powerUpPositions[powerUpY].push_back((int)(SCR.getBoundaryL() + (16 * j)));
				powerUpPositions[powerUpY].push_back((int)(SCR.getBoundaryU() + (16 * i)));
				powerUpY++;
			}
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
#if DEBUG == 0
	createSomeTanks();
#endif
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
			map[y][x] = nullptr;
		}
		delete objToDelete;
		objToDelete = nullptr;
	}

	deletionList.clear();

#if DEBUG == 0
	createPowerUp();
	if (killCount >= 20)
	{
		setGameOverState();
	}
#endif
}

void battleCity::WorldManager::draw()
{
	ObjectListIterator it = ObjectListIterator(&worldList);

	drawBackground();

	for (it.first(); !it.isDone(); it.next())
	{
		(*it.currentObject())->draw();
	}

	if (gameOver)
	{
		GM.gameOverState();
		if (gameOverPos.y != 247)
		{
			gameOverPos.y--;
		}
		drawSprite(gameOverSpr, (int)gameOverPos.x, (int)gameOverPos.y);
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
			Object* tempObject = nullptr;

			for (it.first(); !it.isDone(); it.next())
			{
				tempObject = *it.currentObject();
				EventCollision collision(ptrObject, tempObject, where);

				ptrObject->eventHandler(&collision);
				tempObject->eventHandler(&collision);

				if (ptrObject->isSolid() && tempObject->isSolid())
					doMove = false;
			}
			tempObject = nullptr;

			if (!doMove)
			{
				ptrObject = nullptr;
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

	ptrObject = nullptr;
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
	objectPtr = nullptr;
	return 0;
}

void battleCity::WorldManager::createPowerUp()
{
	if (powerUpPositions.size() != 0)
	{
		switch (killCount)
		{
		case 4:
			if (!isPowerUp && !powerUpisTaked)
			{
				powerUp = new PowerUp(1);
				isPowerUp = true;
			}
			break;
		case 10:
			if (isPowerUp)
			{
				markForDelete(powerUp);
				powerUpisTaked = false;
			}
			else
			{
				powerUpisTaked = false;
			}
			break;
		case 11:
			if (!isPowerUp && !powerUpisTaked)
			{
				powerUp = new PowerUp(1);
				isPowerUp = true;
			}
			break;
		case 17:
			if (isPowerUp)
			{
				markForDelete(powerUp);
				powerUpisTaked = false;
			}
			else
			{
				powerUpisTaked = false;
			}
			break;
		case 18:
			if (!isPowerUp && !powerUpisTaked)
			{
				powerUp = new PowerUp(1);
				isPowerUp = true;
			}
			break;
		}
	}
}

void battleCity::WorldManager::setPowerUpToFalse()
{
	isPowerUp = false;
}

void battleCity::WorldManager::setPowerUpisTakedToTrue()
{
	powerUpisTaked = true;
}

battleCity::ObjectList battleCity::WorldManager::getCollisions(const Object* ptrObject, Vector where) const
{
	ObjectList collisionList;
	if (ptrObject->getSpeed() == 0)
	{
		ptrObject = nullptr;
		return collisionList;
	}
	ObjectListIterator it = ObjectListIterator(&objectsToMove);
	Object* tempObject = nullptr;
	Vector objWorldIndex = ptrObject->getWorldIndexRelative();

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
	if (tempObject == nullptr)
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

	tempObject = nullptr;
	ptrObject = nullptr;
	return collisionList;
}

battleCity::WorldManager::~WorldManager()
{
#if DEBUG == 2
	std::cout << "WorldManager Destructor" << std::endl;
	std::cout << std::endl;
#endif
}