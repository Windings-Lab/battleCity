#include "PhoenixAndFlag.h"

namespace battleCity
{
	PhoenixAndFlag::PhoenixAndFlag(float x, float y) : Object(Type::PhoenixAndFlag)
	{
	}


	void PhoenixAndFlag::Draw()
	{
		// drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}

	void PhoenixAndFlag::OnHit(EventCollision& collisionEvent)
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
