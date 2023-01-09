#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object
{
	class Object;
}

namespace BattleCity::Game::World::Object::Component
{
	class Collider
	{
	public:
		Collider(Object&);

		void ResolveCollisions(const Object&);

		void SetPreviousPosition(const Position&) noexcept;

	private:
		Object& mObject;

		Position mPrevious;
	};
}
