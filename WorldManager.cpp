#include "Manager.h"
#include "WorldManager.h"
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
#include <memory>

using namespace std::string_view_literals;

int battleCity::WorldManager::mWorldId = 1;
int battleCity::WorldManager::mOveId = 1;

battleCity::WorldManager::WorldManager()
{
	SetType(ManagerType::World);
	mMap = std::vector<std::vector<Object*>>(HEIGHT, std::vector<Object*>(WIDTH));
	mPowerUpPositions = std::vector<std::vector<int>>(0, std::vector<int>(0));

	mGameOverPos.x = 290;
	mGameOverPos.y = 600;
	mGameOver = false;

	mTankCount = 0;
	mKillCount = 0;
	mTankStorage = 20;

	mPowerUp = nullptr;
	mIsPowerUp = false;
	mPowerUpTaked = false;
}

battleCity::WorldManager& battleCity::WorldManager::GetInstance()
{
	static WorldManager single;
	return single;
}

int battleCity::WorldManager::StartUp(TankPlayer& newPlayer)
{
	//std::cout << "WorldManager - startUp" << std::endl;
	if(InitMap(newPlayer) == 0)
	    return 0;
	mGameOverSpr = &SPR.getGameOverSprite();
	return Manager::StartUp();
}

void battleCity::WorldManager::ShutDown()
{
	//std::cout << "WorldManager - shutDown" << std::endl;
	ObjectList listToDelete = mWorldList;
	ObjectListIterator it = ObjectListIterator(&listToDelete);
	for (it.first(); !it.isDone(); it.next())
	{
		delete *it.currentObject();
	}
	Manager::ShutDown();
}

void battleCity::WorldManager::SetGameOverState()
{
	if (mGameOver)
		return;
	GM.setStepCount(1);
	GM.setPlayerHealthToZero();
	mGameOver = true;
}

void battleCity::WorldManager::SetTankCount(int newTankCount)
{
	mTankCount += newTankCount;
}

int battleCity::WorldManager::GetTankCount()
{
	return mTankCount;
}

void battleCity::WorldManager::SetKillCount(int newKillCount)
{
	mKillCount += newKillCount;
}

int battleCity::WorldManager::GetKillCount()
{
	return mKillCount;
}

int battleCity::WorldManager::InsertObject(Object* objectPtr)
{
	//std::cout << "WorldManager - insertObject" << std::endl;
	int check;
	if (objectPtr->getWorldMoveID() != 0)
	{
		mOveId++;
		check = mObjectsToMove.insert(objectPtr);
		if (check == -1)
			return check;
	}
	mWorldId++;
	check = mWorldList.insert(objectPtr);
	objectPtr = nullptr;
	return check;
}

int battleCity::WorldManager::RemoveObject(Object* objectPtr)
{
	//std::cout << "WorldManager - removeObject" << std::endl;
	int check;
	if (objectPtr->getWorldMoveID() != 0)
	{
		check = mObjectsToMove.RemoveByMoveId(objectPtr->getWorldMoveID());
		if (check == -1)
			return check;
	}
	check = mWorldList.RemoveByWorldId(objectPtr->getWorldID());
	objectPtr = nullptr;
	return check;
}

battleCity::ObjectList battleCity::WorldManager::GetAllObjects() const
{
	return mWorldList;
}

int battleCity::WorldManager::GetSizeOfWorldList()
{
	return mWorldList.GetSize();
}

int battleCity::WorldManager::GetSizeOfMoveList()
{
	return mObjectsToMove.GetSize();
}

int battleCity::WorldManager::GetWorldId() const
{
	return mWorldId;
}

int battleCity::WorldManager::GetMoveId() const
{
	return mOveId;
}

std::vector<std::vector<battleCity::Object*>>& battleCity::WorldManager::GetWorldMap()
{
	return mMap;
}

std::vector<std::vector<int>>& battleCity::WorldManager::GetPowerUpPositions()
{
	return mPowerUpPositions;
}

void battleCity::WorldManager::CreateSomeTanks()
{
	int rnd = randomNumber(0, 1);
	if (GM.stepCount % 450 == 0 && mTankCount != 6 && mTankStorage > 0)
	{
		if (rnd == 1)
			new Tank(500, 45);
		else
			new Tank(275, 45);
	}
}

int battleCity::WorldManager::InitMap(TankPlayer& newPlayer)
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
				mMap[i][j] = new Wall(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
			else if (charToStore - '0' == 1)
				newPlayer.setPosition(Vector(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i)));
			else if (charToStore - '0' == 2)
				new Tank(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
			else if (charToStore - '0' == 5)
				new PhoenixAndFlag(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
			else if (charToStore - '0' == 7)
			{
				mPowerUpPositions.push_back(std::vector<int>());
				mPowerUpPositions[powerUpY].push_back((int)(SCR.getBoundaryL() + (16 * j)));
				mPowerUpPositions[powerUpY].push_back((int)(SCR.getBoundaryU() + (16 * i)));
				powerUpY++;
			}
		}
	}
	mapFile.close();
	return 1;
}

battleCity::ObjectList battleCity::WorldManager::ObjectsOfType(std::string type)
{
	ObjectList newList = mWorldList;
	ObjectListIterator it = ObjectListIterator(&mWorldList);

	for (it.first(); !it.isDone(); it.next())
	{
		if ((*it.currentObject())->getType() == type)
			newList.insert(*it.currentObject());
	}

	return newList;
}

void battleCity::WorldManager::Update()
{
#if DEBUG == 0
	CreateSomeTanks();
#endif
	//std::cout << "WorldManager - update" << std::endl;
	ObjectList listToIt = mObjectsToMove;
	ObjectListIterator it = ObjectListIterator(&mObjectsToMove);

	ObjectListIterator itUpdate = ObjectListIterator(&mWorldList);
	ObjectListIterator itDeletetion = ObjectListIterator(&mDeletionList);

	for (itUpdate.first(); !itUpdate.isDone(); itUpdate.next())
	{
		(*itUpdate.currentObject())->update();
	}

	for (it.first(); !it.isDone(); it.next())
	{
		Vector newPos = (*it.currentObject())->predictPosition();
		MoveObject(*it.currentObject(), newPos);
	}

	for (itDeletetion.first(); !itDeletetion.isDone(); itDeletetion.next())
	{
		Object* objToDelete = *itDeletetion.currentObject();
		if (objToDelete->getType() == "Wall")
		{
			Vector pos = objToDelete->getPosition();
			int x = (pos.x - SCR.getBoundaryL()) / 16;
			int y = (pos.y - SCR.getBoundaryU()) / 16;
			mMap[y][x] = nullptr;
		}
		delete objToDelete;
		objToDelete = nullptr;
	}

	mDeletionList.Clear();

#if DEBUG == 0
	CreatePowerUp();
	if (mKillCount >= 20)
	{
		SetGameOverState();
	}
#endif
}

void battleCity::WorldManager::Draw()
{
	ObjectListIterator it = ObjectListIterator(&mWorldList);

	DrawBackground();

	for (it.first(); !it.isDone(); it.next())
	{
		(*it.currentObject())->draw();
	}

	if (mGameOver)
	{
		GM.gameOverState();
		if (mGameOverPos.y != 247)
		{
			mGameOverPos.y--;
		}
		drawSprite(mGameOverSpr, (int)mGameOverPos.x, (int)mGameOverPos.y);
	}
}

void battleCity::WorldManager::DrawBackground()
{

	drawSprite(&SPR.getBackgroundSprite(), SCR.getBoundaryL(), SCR.getBoundaryU());
}

int battleCity::WorldManager::MoveObject(Object* ptrObject, Vector where)
{
	//std::cout << "moveObject" << std::endl;
	if (ptrObject->isSolid() || ptrObject->isSoft())
	{
		ObjectList newList = GetCollisions(ptrObject, where);

		if (!newList.IsEmpty())
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
		auto eventOut = std::make_unique<EventOut>();
		ptrObject->eventHandler(eventOut.get());
	}

	ptrObject = nullptr;
	return i;
}

int battleCity::WorldManager::MarkForDelete(Object* objectPtr)
{
	ObjectListIterator it = ObjectListIterator(&mDeletionList);

	for (it.first(); !it.isDone(); it.next())
	{
		if (*it.currentObject() == objectPtr)
			return 0;
	}

	objectPtr->setHealth(-1);

	if (objectPtr->getHealth() == 0)
	{
		mDeletionList.insert(objectPtr);
	}
	objectPtr = nullptr;
	return 0;
}

void battleCity::WorldManager::CreatePowerUp()
{
	if (mPowerUpPositions.size() != 0)
	{
		switch (mKillCount)
		{
		case 4:
			if (!mIsPowerUp && !mPowerUpTaked)
			{
				mPowerUp = new PowerUp(1);
				mIsPowerUp = true;
			}
			break;
		case 10:
			if (mIsPowerUp)
			{
				MarkForDelete(mPowerUp);
				mPowerUpTaked = false;
			}
			else
			{
				mPowerUpTaked = false;
			}
			break;
		case 11:
			if (!mIsPowerUp && !mPowerUpTaked)
			{
				mPowerUp = new PowerUp(1);
				mIsPowerUp = true;
			}
			break;
		case 17:
			if (mIsPowerUp)
			{
				MarkForDelete(mPowerUp);
				mPowerUpTaked = false;
			}
			else
			{
				mPowerUpTaked = false;
			}
			break;
		case 18:
			if (!mIsPowerUp && !mPowerUpTaked)
			{
				mPowerUp = new PowerUp(1);
				mIsPowerUp = true;
			}
			break;
		}
	}
}

void battleCity::WorldManager::SetPowerUpToFalse()
{
	mIsPowerUp = false;
}

void battleCity::WorldManager::SetPowerUpisTakedToTrue()
{
	mPowerUpTaked = true;
}

battleCity::ObjectList battleCity::WorldManager::GetCollisions(const Object* ptrObject, Vector where) const
{
	ObjectList collisionList;
	if (ptrObject->getSpeed() == 0)
	{
		ptrObject = nullptr;
		return collisionList;
	}
	ObjectListIterator it = ObjectListIterator(&mObjectsToMove);
	Object* tempObject = nullptr;
	Vector objWorldIndex = ptrObject->getWorldIndexRelative();

	tempObject = mMap[(int)objWorldIndex.y][(int)objWorldIndex.x];
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