#include "Manager.h"
#include "Object.h"
#include "WorldManager.h"

namespace battleCity
{
	Manager::Manager(ManagerType type) : mType(type) {}
	Manager::~Manager() {}

	bool Manager::GetStarted() const
	{
		return mStarted;
	}

	ManagerType Manager::GetType() const
	{
		return mType;
	}

	void Manager::SendEvent(Event& eventRef) const
	{
		for (const int objID : WM.GetObjectsToMove())
		{
			WM.GetAllObjects().GetObject(objID).EventHandler(eventRef);
		}

		for (const int objID : WM.GetObjectsOfType(Object::Type::Explosion))
		{
			WM.GetAllObjects().GetObject(objID).EventHandler(eventRef);
		}
	}
}
