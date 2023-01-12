#include "PCHeader.h"
#include "Observer.h"

#include "Subject.h"

namespace BattleCity
{
	Observer::Observer(std::shared_ptr<Subject> subject)
		: mSubject(subject)
	{
	}

	Observer::~Observer()
	{
		if(!mSubject.expired())
		{
			mSubject.lock()->UnregisterObserver(shared_from_this());
		}
	}
}
