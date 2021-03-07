#include "WorldManager.h"

battleCity::WorldManager::WorldManager()
{
	worldList = new ObjectList();
	setType("GameManager");
}

battleCity::WorldManager::~WorldManager()
{
	delete worldList;
	worldList = NULL;
}

battleCity::WorldManager& battleCity::WorldManager::getInstance()
{
	static WorldManager single;
	single.startUp();
	return single;
}

int battleCity::WorldManager::startUp()
{
	return Manager::startUp();
}

void battleCity::WorldManager::shutDown()
{
	//ObjectList* all = worldList;
	//all->clear(all);

	Manager::shutDown();
}

//int battleCity::WorldManager::insertObject(Object* objectPtr)
//{
//	return worldList->insert(objectPtr);
//}
//
//int battleCity::WorldManager::removeObject(Object* objectPtr)
//{
//	return worldList->remove(objectPtr);
//}

battleCity::ObjectList* battleCity::WorldManager::getAllObjects() const
{
	return worldList;
}

battleCity::ObjectList* battleCity::WorldManager::objectsOfType(string type)
{
	ObjectList* newList = worldList;
	return new ObjectList();
}
