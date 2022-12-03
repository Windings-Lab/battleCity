#include "WorldManager.h"
#include "Object.h"
#include "PhoenixAndFlag.h"
#include "Tank.h"
#include "Utility.h"
#include "Screen.h"
#include "Wall.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "PowerUp.h"
#include "Vector.h"
#include "Box.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_set>

#include "GameManager.h"

using namespace std::string_view_literals;

namespace battleCity
{
	WorldManager::WorldManager()
		: Manager(ManagerType::World)
		  , mMap(std::vector(HEIGHT, std::vector<int>(WIDTH)))
		  , mPowerUpPositions(std::vector(0, std::vector<int>(0)))
	{
		mPlayerID = 0;

		mGameOverSpr = nullptr;
		mGameOverPos.X = 290;
		mGameOverPos.Y = 600;

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

	void WorldManager::StartUp()
	{
		InitMap();
		mGameOverSpr = &SPR.getGameOverSprite();
	}

	void WorldManager::ShutDown()
	{
		mWorldList.Clear();
	}

	void WorldManager::IncrementTankCount(int count)
	{
		mTankCount += count;
	}

	int WorldManager::GetTankCount()
	{
		return mTankCount;
	}

	void WorldManager::IncrementKillCount(int newKillCount)
	{
		mKillCount += newKillCount;
	}

	int WorldManager::GetKillCount()
	{
		return mKillCount;
	}

	void WorldManager::InsertObject(std::unique_ptr<Object>& objPtr)
	{
		if (objPtr->IsMovable())
		{
			mObjectIDsToMove.insert(objPtr->GetID());
		}

		mWorldList.Insert(objPtr);
	}

	void WorldManager::RemoveObject(int objID)
	{
		mObjectIDsToMove.erase(objID);
		mWorldList.Remove(objID);
	}

	const ObjectList& WorldManager::GetAllObjects() const
	{
		return mWorldList;
	}

	std::unordered_set<int> WorldManager::GetObjectsToMove() const
	{
		return mObjectIDsToMove;
	}

	int WorldManager::GetObjectCount() const
	{
		return mWorldList.GetSize();
	}

	void WorldManager::SetPlayerID(int playerID)
	{
		mPlayerID = playerID;
	}

	int WorldManager::GetPlayerID() const
	{
		return mPlayerID;
	}

	void WorldManager::SetPlayerHealthToZero() const
	{
		auto& player = mWorldList.GetObject(GetPlayerID());
		player.SetHealth(-player.GetHealth());
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
		if (GM.GetStepCount() % 450 == 0 && mTankCount != 6 && mTankStorage > 0)
		{
			if (rnd == 1)
			{
				std::unique_ptr<Object> tank = std::make_unique<Tank>(500, 45);
				InsertObject(tank);
			}
			else
			{
				std::unique_ptr<Object> tank = std::make_unique<Tank>(275, 45);
				InsertObject(tank);
			}
		}
	}

	void WorldManager::InitMap()
	{
		//std::cout << "WorldManager - initMap" << std::endl;
		char charToStore;
		std::ifstream mapFile(".\\data\\Maps\\level1.txt");
		if (!mapFile)
		{
			std::cout << "Map not found" << std::endl;
			throw;
		}

		int powerUpY = 0;
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				mapFile >> charToStore;

				switch (auto type = static_cast<Object::ObjectType>(charToStore - '0'))
				{
				case Object::Type::TankPlayer:
					{
						auto& newPlayer = mWorldList.GetObject(mPlayerID);
						newPlayer.SetPosition(Vector(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i)));
						break;
					}
				case Object::Type::Tank:
					{
						std::unique_ptr<Object> tank = std::make_unique<Tank>(
							SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
						InsertObject(tank);
						break;
					}
				case Object::Type::Bullet: break;
				case Object::Type::Wall:
					{
						std::unique_ptr<Object> wall = std::make_unique<Wall>(
							SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
						mMap[i][j] = wall->GetID();
						InsertObject(wall);
						break;
					}
				case Object::Type::PhoenixAndFlag:
					{
						std::unique_ptr<Object> phoenixAndFlag = std::make_unique<PhoenixAndFlag>
							(SCR.getBoundaryL() + (16 * j), SCR.getBoundaryU() + (16 * i));
						InsertObject(phoenixAndFlag);
						break;
					}
				case Object::Type::Explosion: break;
				case Object::Type::PowerUp:
					mPowerUpPositions.push_back(std::vector<int>());
					mPowerUpPositions[powerUpY].push_back(static_cast<int>((SCR.getBoundaryL() + (16 * j))));
					mPowerUpPositions[powerUpY].push_back(static_cast<int>((SCR.getBoundaryU() + (16 * i))));
					powerUpY++;
					break;
				case Object::Type::Error:
				default: break;
				}
			}
		}
		mapFile.close();
	}

	std::unordered_set<int> WorldManager::GetObjectsOfType(Object::ObjectType type) const
	{
		std::unordered_set<int> newList;
		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			if (objRef->GetType() == type)
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
			objRef->Update();
		}

		for (const int objID : mObjectIDsToMove)
		{
			Object& objPtr = mWorldList.GetObject(objID);
			MoveObject(objPtr, objPtr.PredictPosition());
		}

		for (const int objID : mObjectIDsToDelete)
		{
			const Object& objPtr = mWorldList.GetObject(objID);
			if (objPtr.GetType() == Object::Type::Wall)
			{
				Vector pos = objPtr.GetPosition();
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
			GM.SetGameOverState();
		}
#endif
	}

	void WorldManager::Draw()
	{
		DrawBackground();

		for (const auto& [objID, objRef] : mWorldList.GetRange())
		{
			objRef->Draw();
		}

		if (GM.GetGameOverState() && !GM.GameOverTimerEnded())
		{
			if (mGameOverPos.Y != 247)
			{
				mGameOverPos.Y--;
			}
			drawSprite(mGameOverSpr, static_cast<int>(mGameOverPos.X), static_cast<int>(mGameOverPos.Y));
		}
	}

	void WorldManager::DrawBackground()
	{
		drawSprite(&SPR.getBackgroundSprite(), SCR.getBoundaryL(), SCR.getBoundaryU());
	}

	void WorldManager::MoveObject(Object& movableObj, Vector where)
	{
		//std::cout << "moveObject" << std::endl;
		if (movableObj.IsSolid() || movableObj.IsSoft())
		{
			if (auto newList = GetCollisions(movableObj, where); !newList.empty())
			{
				bool doMove = true;

				for (const auto& objID : newList)
				{
					auto& colliderObj = mWorldList.GetObject(objID);
					EventCollision collision(movableObj.GetID(), colliderObj.GetID(), where);

					movableObj.EventHandler(collision);
					colliderObj.EventHandler(collision);

					doMove = !(movableObj.IsSolid() && colliderObj.IsSolid());
				}

				if (!doMove)
				{
					return;
				}
			}
		}

		int i = 0;
		if ((where.X >= SCR.getBoundaryL() && where.X + movableObj.getSpriteX() <= SCR.getBoundaryR()) &&
			(where.Y >= SCR.getBoundaryU() && where.Y + movableObj.getSpriteY() <= SCR.getBoundaryD()))
		{
			i = movableObj.SetPosition(where);
		}
		else
		{
			auto eventOut = EventOut();
			movableObj.EventHandler(eventOut);
		}
	}

	void WorldManager::MarkForDelete(int objID)
	{
		if (mObjectIDsToDelete.find(objID) != mObjectIDsToDelete.end())
		{
			return;
		}

		auto& objRef = mWorldList.GetObject(objID);

		objRef.SetHealth(-1);

		if (objRef.GetHealth() == 0)
		{
			mObjectIDsToDelete.insert(objID);
		}
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
		if (ptrObject.GetSpeed() == 0)
		{
			return collisionList;
		}
		Vector objWorldIndex = ptrObject.getWorldIndexRelative();

		int mapObjID = mMap[static_cast<int>(objWorldIndex.Y)][static_cast<int>(objWorldIndex.X)];
		auto iterateFullListFunc = [&]
		{
			for (const auto& [objID, colliderObj] : mWorldList.GetRange())
			{
				if (mapObjID == 0) continue;
				Object& tempObject = mWorldList.GetObject(mapObjID);
				if (objID == ptrObject.GetID())
				{
					continue;
				}
				Box b = getWorldBox(ptrObject, where);
				Box bTemp = getWorldBox(tempObject);
				if ((tempObject.IsSolid() || tempObject.IsSoft()) &&
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
				(tempObject.IsSolid() || tempObject.IsSoft()))
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
}
