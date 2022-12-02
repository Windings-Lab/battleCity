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

#include "Object.h"

using namespace std::string_view_literals;

namespace battleCity
{
	WorldManager::WorldManager()
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

	WorldManager& WorldManager::GetInstance()
	{
		static WorldManager single;
		return single;
	}

	int WorldManager::StartUp(TankPlayer& newPlayer)
	{
		//std::cout << "WorldManager - startUp" << std::endl;
		if (InitMap(newPlayer) == 0)
			return 0;
		mGameOverSpr = &SPR.getGameOverSprite();
		return Manager::StartUp();
	}

	void WorldManager::ShutDown()
	{
		//std::cout << "WorldManager - shutDown" << std::endl;
		mWorldList.Clear();
		Manager::ShutDown();
	}

	void WorldManager::SetGameOverState()
	{
		if (mGameOver)
			return;
		GM.setStepCount(1);
		GM.setPlayerHealthToZero();
		mGameOver = true;
	}

	void WorldManager::SetTankCount(int newTankCount)
	{
		mTankCount += newTankCount;
	}

	int WorldManager::GetTankCount()
	{
		return mTankCount;
	}

	void WorldManager::SetKillCount(int newKillCount)
	{
		mKillCount += newKillCount;
	}

	int WorldManager::GetKillCount()
	{
		return mKillCount;
	}

	int WorldManager::InsertObject(const std::unique_ptr<Object>& objPtr)
	{
		//std::cout << "WorldManager - insertObject" << std::endl;
		if (objPtr->IsMovable())
		{
			mObjectIDsToMove.insert(objPtr->GetID());
		}
		
		return mWorldList.Insert(objPtr);
	}

	int WorldManager::RemoveObject(int objID)
	{
		//std::cout << "WorldManager - removeObject" << std::endl;
		mObjectIDsToMove.erase(objID);
		return mWorldList.Remove(objID);
	}

	const ObjectList& WorldManager::GetAllObjects() const
	{
		return mWorldList;
	}

	int WorldManager::GetSizeOfWorldList() const
	{
		return mWorldList.GetSize();
	}

	std::vector<std::vector<Object*>>& WorldManager::GetWorldMap()
	{
		return mMap;
	}

	std::vector<std::vector<int>>& WorldManager::GetPowerUpPositions()
	{
		return mPowerUpPositions;
	}

	void WorldManager::CreateSomeTanks()
	{
		int rnd = randomNumber(0, 1);
		if (GM.stepCount % 450 == 0 && mTankCount != 6 && mTankStorage > 0)
		{
			if (rnd == 1)
				InsertObject(std::make_unique<Tank>(500, 45));
			else
				InsertObject(std::make_unique<Tank>(275, 45));
		}
	}

	int WorldManager::InitMap(TankPlayer& newPlayer)
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

	std::unordered_set<int> WorldManager::GetObjectsOfType(Object::Type type) const
	{
		std::unordered_set<int> newList;
		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			if (objRef->getType() == type)
				newList.insert(objRef->GetID());
		}

		return newList;
	}

	void WorldManager::Update()
	{
#if DEBUG == 0
		CreateSomeTanks();
#endif
		//std::cout << "WorldManager - update" << std::endl;

		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			objRef->update();
		}

		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			if(mObjectIDsToMove.find(objID) != mObjectIDsToMove.end())
			{
				Vector newPos = objRef->predictPosition();
				MoveObject(objRef, newPos);
			}
		}

		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			if (mObjectIDsToDelete.find(objID) != mObjectIDsToDelete.end())
			{
				if (objRef->getType() == Object::Type::Wall)
				{
					Vector pos = objRef->getPosition();
					int x = (pos.x - SCR.getBoundaryL()) / 16;
					int y = (pos.y - SCR.getBoundaryU()) / 16;
					mMap[y][x] = nullptr;
				}
				RemoveObject(objID);
			}
		}

		mObjectIDsToDelete.clear();

#if DEBUG == 0
		CreatePowerUp();
		if (mKillCount >= 20)
		{
			SetGameOverState();
		}
#endif
	}

	void WorldManager::Draw()
	{
		DrawBackground();

		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			objRef->draw();
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

	void WorldManager::DrawBackground()
	{
		drawSprite(&SPR.getBackgroundSprite(), SCR.getBoundaryL(), SCR.getBoundaryU());
	}

	int WorldManager::MoveObject(const std::unique_ptr<Object>& movableObjt, Vector where)
	{
		//std::cout << "moveObject" << std::endl;
		if (movableObjt->isSolid() || movableObjt->isSoft())
		{
			ObjectList newList = GetCollisions(movableObjt, where);

			if (!newList.IsEmpty())
			{
				bool doMove = true;

				for (const auto& [objID, colliderObj] : newList.GetRange())
				{
					EventCollision collision(movableObjt, colliderObj, where);

					movableObjt->eventHandler(&collision);
					colliderObj->eventHandler(&collision);

					if (movableObjt->isSolid() && colliderObj->isSolid()) doMove = false;
				}

				if (!doMove)
				{
					return -1;
				}
			}
		}

		int i = 0;
		if ((where.x >= SCR.getBoundaryL() && where.x + movableObjt->getSpriteX() <= SCR.getBoundaryR()) &&
			(where.y >= SCR.getBoundaryU() && where.y + movableObjt->getSpriteY() <= SCR.getBoundaryD()))
		{
			i = movableObjt->setPosition(where);
		}
		else
		{
			auto eventOut = std::make_unique<EventOut>();
			movableObjt->eventHandler(eventOut.get());
		}

		return i;
	}

	int WorldManager::MarkForDelete(int objID)
	{
		if (mObjectIDsToDelete.find(objID) != mObjectIDsToDelete.end())
		{
			return 0;
		}

		const auto objRef = mWorldList.GetObject(objID);

		objRef->setHealth(-1);

		if (objRef->getHealth() == 0)
		{
			mObjectIDsToDelete.insert(objID);
		}
		
		return 0;
	}

	void WorldManager::CreatePowerUp()
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
					MarkForDelete(mPowerUp->GetID());
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
					MarkForDelete(mPowerUp->GetID());
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

	void WorldManager::SetPowerUpToFalse()
	{
		mIsPowerUp = false;
	}

	void WorldManager::SetPowerUpisTakedToTrue()
	{
		mPowerUpTaked = true;
	}

	std::unordered_set<int> WorldManager::GetCollisions(const std::unique_ptr<Object>& ptrObject, Vector where) const
	{
		std::unordered_set<int> collisionList;
		if (ptrObject->getSpeed() == 0)
		{
			return collisionList;
		}
		Object* tempObject = nullptr;
		Vector objWorldIndex = ptrObject->getWorldIndexRelative();

		tempObject = mMap[(int)objWorldIndex.y][(int)objWorldIndex.x];
		auto iterateFullListFunc = [&]()
		{
			for (const auto& [objID, colliderObj] : mWorldList.GetRange())
			{
				if (colliderObj == ptrObject)
				{
					continue;
				}
				Box b = getWorldBox(ptrObject, where);
				Box bTemp = getWorldBox(tempObject);
				if ((tempObject->isSolid() || tempObject->isSoft()) && 
					boxesIntersect(b, bTemp))
				{
					collisionList.insert(tempObject->GetID());
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
				collisionList.insert(tempObject->GetID());
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

	WorldManager::~WorldManager()
	{
#if DEBUG == 2
		std::cout << "WorldManager Destructor" << std::endl;
		std::cout << std::endl;
#endif
	}
}
