#include "PCHeader.h"

#include "PowerUp.h"
#include "EventCollision.h"

namespace BattleCity
{
	PowerUp::PowerUp() : Object(Type::PowerUp)
	{
	}

	void PowerUp::Update(const float& deltaTime)
	{

	}


	void PowerUp::EventHandler(Event& event)
	{
		if (event.GetType() == EventType::Collision)
		{
		}
	}
}
