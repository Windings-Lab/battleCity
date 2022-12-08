#include "PCHeader.h"

#include "PowerUp.h"
#include "EventCollision.h"

namespace BattleCity::Object
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
