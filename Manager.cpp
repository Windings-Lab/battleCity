#include "Manager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "Explosion.h"

#include <iostream>

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

	for (const int objID : WM.mObjectIDsToMove)
	{
		auto& movableObject = WM.mWorldList.GetObject(objID);
		movableObject.eventHandler(ptrEvent);
		count++;
	}

	for (const int objID : WM.GetObjectsOfType(Object::Type::Explosion))
	{
		auto& explosionObj = WM.mWorldList.GetObject(objID);
		explosionObj.eventHandler(ptrEvent);
		count++;
	}

	ptrEvent = nullptr;
	return count;
}
