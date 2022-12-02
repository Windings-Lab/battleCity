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
		mMap = std::vector(HEIGHT, std::vector<int>(WIDTH));
		mPowerUpPositions = std::vector(0, std::vector<int>(0));

		mGameOverPos.X = 290;
		mGameOverPos.Y = 600;
		mGameOver = false;

		mTankCount = 0;
		mKillCount = 0;
		mTankStorage = 20;

		mPowerUpID = 0;
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

	std::vector<std::vector<int>>& WorldManager::GetWorldMap()
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
		for (int i = 0; i < HEIGHT; i++) 
		{
			for (int j = 0; j < WIDTH; j++) 
			{
				mapFile >> charToStore;
				auto type = static_cast<Object::Type>(charToStore - '0');

				switch (type)
				{
				case Object::Type::TankPlayer:
					newPlayer.setPosition(Vector(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i)));
					break;
				case Object::Type::Tank:
					InsertObject(std::make_unique<Tank>(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i)));
					break;
				case Object::Type::Bullet: break;
				case Object::Type::Wall:
				{
					std::unique_ptr<Object> wall = std::make_unique<Wall>(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
					InsertObject(wall);
					mMap[i][j] = wall->GetID();
					break;
				}
				case Object::Type::PhoenixAndFlag:
					InsertObject(std::make_unique<PhoenixAndFlag>(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i)));
					break;
				case Object::Type::Explosion: break;
				case Object::Type::PowerUp: 
					mPowerUpPositions.push_back(std::vector<int>());
					mPowerUpPositions[powerUpY].push_back((int)(SCR.getBoundaryL() + (16 * j)));
					mPowerUpPositions[powerUpY].push_back((int)(SCR.getBoundaryU() + (16 * i)));
					powerUpY++;
					break;
				case Object::Type::Error:
				default: break;
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

		for(const int objID : mObjectIDsToMove)
		{
			Object& objPtr = mWorldList.GetObject(objID);
			MoveObject(objPtr, objPtr.predictPosition());
		}

		for (const int objID : mObjectIDsToDelete)
		{
			const Object& objPtr = mWorldList.GetObject(objID);
			if (objPtr.getType() == Object::Type::Wall)
			{
				Vector pos = objPtr.getPosition();
				int x = (pos.X - SCR.getBoundaryL()) / 16;
				int y = (pos.Y - SCR.getBoundaryU()) / 16;
				mMap[y][x] = 0;
			}
			RemoveObject(objID);
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
			if (mGameOverPos.Y != 247)
			{
				mGameOverPos.Y--;
			}
			drawSprite(mGameOverSpr, (int)mGameOverPos.X, (int)mGameOverPos.Y);
		}
	}

	void WorldManager::DrawBackground()
	{
		drawSprite(&SPR.getBackgroundSprite(), SCR.getBoundaryL(), SCR.getBoundaryU());
	}

	int WorldManager::MoveObject(Object& movableObj, Vector where)
	{
		//std::cout << "moveObject" << std::endl;
		if (movableObj.isSolid() || movableObj.isSoft())
		{
			if (auto newList = GetCollisions(movableObj, where); !newList.empty())
			{
				bool doMove = true;

				for (const auto& objID : newList)
				{
					auto& colliderObj = mWorldList.GetObject(objID);
					EventCollision collision(movableObj.GetID(), colliderObj.GetID(), where);

					movableObj.eventHandler(&collision);
					colliderObj.eventHandler(&collision);

					doMove = !(movableObj.isSolid() && colliderObj.isSolid());
				}

				if (!doMove)
				{
					return -1;
				}
			}
		}

		int i = 0;
		if ((where.X >= SCR.getBoundaryL() && where.X + movableObj.getSpriteX() <= SCR.getBoundaryR()) &&
			(where.Y >= SCR.getBoundaryU() && where.Y + movableObj.getSpriteY() <= SCR.getBoundaryD()))
		{
			i = movableObj.setPosition(where);
		}
		else
		{
			auto eventOut = std::make_unique<EventOut>();
			movableObj.eventHandler(eventOut.get());
		}

		return i;
	}

	int WorldManager::MarkForDelete(int objID)
	{
		if (mObjectIDsToDelete.find(objID) != mObjectIDsToDelete.end())
		{
			return 0;
		}

		auto& objRef = mWorldList.GetObject(objID);

		objRef.setHealth(-1);

		if (objRef.getHealth() == 0)
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
					std::unique_ptr<Object> powerUP = std::make_unique<PowerUp>(1);
					InsertObject(powerUP);
					mPowerUpID = powerUP->GetID();
					mIsPowerUp = true;
				}
				break;
			case 10:
				if (mIsPowerUp)
				{
					MarkForDelete(mPowerUpID);
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
					std::unique_ptr<Object> powerUP = std::make_unique<PowerUp>(1);
					InsertObject(powerUP);
					mPowerUpID = powerUP->GetID();
					mIsPowerUp = true;
				}
				break;
			case 17:
				if (mIsPowerUp)
				{
					MarkForDelete(mPowerUpID);
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
					std::unique_ptr<Object> powerUP = std::make_unique<PowerUp>(1);
					InsertObject(powerUP);
					mPowerUpID = powerUP->GetID();
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

	// TODO: Fix
	std::unordered_set<int> WorldManager::GetCollisions(const Object& ptrObject, Vector where) const
	{
		std::unordered_set<int> collisionList;
		if (ptrObject.getSpeed() == 0)
		{
			return collisionList;
		}
		Vector objWorldIndex = ptrObject.getWorldIndexRelative();

		int mapObjID = mMap[(int)objWorldIndex.Y][(int)objWorldIndex.X];
		auto iterateFullListFunc = [&]
		{
			for (const auto& [objID, colliderObj] : mWorldList.GetRange())
			{
				Object& tempObject = mWorldList.GetObject(mapObjID);
				if (objID == ptrObject.GetID())
				{
					continue;
				}
				Box b = getWorldBox(ptrObject, where);
				Box bTemp = getWorldBox(tempObject);
				if ((tempObject.isSolid() || tempObject.isSoft()) && 
					boxesIntersect(b, bTemp))
				{
					collisionList.insert(tempObject.GetID());
				}
			}
		};
		// IF NULL then check for other movable objects
		if (mapObjID == 0)
		{
			iterateFullListFunc();
		}
		// Else we are checking this wall for collision
		else
		{
			Object& tempObject = mWorldList.GetObject(mapObjID);
			Box b = getWorldBox(ptrObject, where);
			Box bTemp = getWorldBox(tempObject);
			// If false, then check other objects for collision
			// for example Player(14, 0), Wall(15, 0) no collision
			if (boxesIntersect(b, bTemp) &&
				(tempObject.isSolid() || tempObject.isSoft()))
			{
				collisionList.insert(tempObject.GetID());
			}
			// Check other movable objects
			else
			{
				iterateFullListFunc();
			}
		}

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
