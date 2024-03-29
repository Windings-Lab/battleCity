#pragma once

namespace BattleCity::Game::World::Object
{
	class Object;
	class Subject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = 0;

		virtual void OnObjectUpdate(Object&) = 0;
		virtual void OnObjectDelete(Object&) = 0;
	};
}
