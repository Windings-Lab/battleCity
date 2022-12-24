#pragma once

namespace BattleCity::Pattern
{
	class IObserver;

	class ISubject
	{
	protected:
		ISubject() = default;
		virtual ~ISubject() = 0;

	public:
		void Register(int id, IObserver& obs);
		void Remove(int id);

	protected:
		void NotifyObservers() const;

	private:
		std::unordered_map<int, IObserver*> mObservers;
	};
}
