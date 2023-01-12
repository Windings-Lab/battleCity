#pragma once

namespace BattleCity
{
	class Observer;

	class Subject
	{
    public:
		void RegisterObserver(std::shared_ptr<Observer> observer);

        void UnregisterObserver(std::shared_ptr<Observer> observer);

        void NotifyObservers() const;

    private:
        std::list<std::weak_ptr<Observer>> mObservers;
	};
}
