#pragma once

namespace BattleCity::Game::World::Object
{
	class Object;
	class Observer;

	class Subject
	{
    public:
		explicit Subject(const Object*);

		DISALLOW_COPY_MOVE(Subject)

		virtual ~Subject();

		void RegisterObserver(Observer* observer);

        void UnregisterObserver(Observer* observer);

        void NotifyOnObjectUpdate() const;

    private:
        std::list<Observer*> mObservers;
		const Object* mObjectRef;
	};
}
