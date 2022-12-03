#include "Manager.h"
#include "WorldManager.h"
#include "Object.h"

namespace battleCity
{
	Manager::Manager(ManagerType type) : mType(type) {}

	ManagerType Manager::GetType() const
	{
		return mType;
	}

	void Manager::SendEvent(Event& eventRef) const
	{
		for (const int objID : WM.mObjectIDsToMove)
		{
			WM.mWorldList.GetObject(objID).EventHandler(eventRef);
		}

		for (const int objID : WM.GetObjectsOfType(Object::Type::Explosion))
		{
			WM.mWorldList.GetObject(objID).EventHandler(eventRef);
		}
	}
}
