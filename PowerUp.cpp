#include "PowerUp.h"
#include "EventCollision.h"

namespace battleCity
{
	PowerUp::PowerUp() : Object(Type::PowerUp)
	{
	}

	void PowerUp::Update()
	{

	}


	void PowerUp::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Collision)
		{
		}
	}
}
