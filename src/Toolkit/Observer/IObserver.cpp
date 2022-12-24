#include "PCHeader.h"
#include "IObserver.h"

#include "ISubject.h"
#include "UUID.h"

namespace BattleCity::Pattern
{
	IObserver::~IObserver() = default;

	void IObserver::Subscribe(ISubject& mailer)
	{
		mailer.Register(dynamic_cast<UUID&>(*this).GetID(), *this);
	}
}

