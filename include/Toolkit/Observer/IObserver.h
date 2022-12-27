#pragma once

namespace BattleCity::Pattern
{
	class ISubject;

	class IObserver
	{
	public:
		virtual ~IObserver() = 0;

		virtual void Subscribe(ISubject& mailer) = 0;
		virtual void Recieve(const ISubject& mailer) = 0;
	};
}
