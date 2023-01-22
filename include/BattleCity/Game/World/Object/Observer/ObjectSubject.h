#pragma once

namespace BattleCity::Game::World::Object
{
	class Object;
	class Observer;

	class Subject
	{
    protected:
		Subject();

		DISALLOW_COPY_MOVE(Subject)

		virtual ~Subject();

	public:
		void RegisterObserver(Observer* observer);
        void UnregisterObserver(Observer* observer);

	protected:
        void NotifyObjectUpdated(Object&) const;
		void NotifyObjectDeleted(const Object&) const;

    private:
        std::vector<Observer*> mObservers;
	};
}
