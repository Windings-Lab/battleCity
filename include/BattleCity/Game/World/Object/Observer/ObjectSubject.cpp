#include "PCHeader.h"
#include "ObjectSubject.h"

#include "ObjectObserver.h"
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	Subject::Subject() = default;
	Subject::~Subject() = default;

	void Subject::RegisterObserver(Observer* observer)
	{
		mObservers.emplace_back(observer);
	}
	void Subject::UnregisterObserver(Observer* observer)
	{
		mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
	}

	void Subject::NotifyObjectUpdated(Object& obj) const
	{
		for (const auto& observer : mObservers)
		{
			observer->OnObjectUpdate(obj);
		}
	}
	void Subject::NotifyObjectDeleted(const Object& obj) const
	{
		for (const auto& observer : mObservers)
		{
			observer->OnObjectDelete(obj);
		}
	}
}

