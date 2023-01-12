#include "PCHeader.h"
#include "Subject.h"

#include "Observer.h"

namespace BattleCity
{
	void Subject::RegisterObserver(std::shared_ptr<Observer> observer)
	{
		mObservers.emplace_back(observer);
	}
	void Subject::UnregisterObserver(std::shared_ptr<Observer> observer)
	{
		observer->PreUnregister();
		mObservers.remove(observer);
	}

	void Subject::NotifyObservers() const
	{
		for (const auto& observerWeak : mObservers)
		{
			observerWeak.lock()->OnNotify();
		}
	}
}

