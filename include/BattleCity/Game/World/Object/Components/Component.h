#pragma once

namespace BattleCity::Game::World::Object
{
	class Object;
}

namespace BattleCity::Game::World::Object::Component
{
	class Component
	{
	public:
		explicit Component(Object& object);
		virtual ~Component() = 0;

	protected:
		Object& mObject;

	};
}
