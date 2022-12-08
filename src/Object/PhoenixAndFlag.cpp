#include "PCHeader.h"

#include "PhoenixAndFlag.h"

namespace BattleCity::Object
{
	PhoenixAndFlag::PhoenixAndFlag(float x, float y) : Object(Type::PhoenixAndFlag)
	{
	}

	void PhoenixAndFlag::OnHit(EventCollision& collisionEvent)
	{

	}

	void PhoenixAndFlag::Update()
	{

	}

	void PhoenixAndFlag::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Collision)
		{
			OnHit(dynamic_cast<EventCollision&>(event));
		}
	}
}
