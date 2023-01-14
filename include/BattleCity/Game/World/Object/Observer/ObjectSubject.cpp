#include "PCHeader.h"
#include "ObjectSubject.h"

#include "ObjectObserver.h"

namespace BattleCity::Game::World::Object
{
	Subject::Subject(const Object* obj) : mObjectRef(obj) {}

	Subject::~Subject()
	{
		for (const auto& observer : mObservers)
		{
			observer->OnObjectDelete(mObjectRef);
		}
	}

	void Subject::RegisterObserver(Observer* observer)
	{
		mObservers.emplace_back(observer);
	}
	void Subject::UnregisterObserver(Observer* observer)
	{
		mObservers.remove(observer);
	}

	void Subject::NotifyOnObjectUpdate() const
	{
		for (const auto& observer : mObservers)
		{
			observer->OnObjectUpdate(mObjectRef);
		}
	}
}

