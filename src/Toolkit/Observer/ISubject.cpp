#include "PCHeader.h"
#include "ISubject.h"

#include "IObserver.h"

namespace BattleCity::Pattern
{
	ISubject::~ISubject() = default;

	void ISubject::Register(int id, IObserver& obs)
	{
		mObservers.try_emplace(id, &obs);
	}

	void ISubject::Remove(int id)
	{
		mObservers.erase(id);
	}

	void ISubject::NotifyObservers() const
	{
		for (const auto& [id, observer] : mObservers)
		{
			observer->Recieve(*this);
		}
	}
}

