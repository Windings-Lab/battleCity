#include "PowerUp.h"
#include "EventCollision.h"

namespace battleCity
{
	PowerUp::PowerUp() : Object(Type::PowerUp)
	{
	}

	void PowerUp::Draw()
	{
		// drawSprite(mSprite, (int)mPosition.X, (int)mPosition.Y);
	}


	void PowerUp::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Collision)
		{
		}
	}
}
