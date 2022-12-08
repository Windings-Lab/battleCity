#pragma once

#include "Tank.h"

namespace BattleCity::Event
{
	class EventCollision;
}

namespace BattleCity::Object
{
	class TankPlayer final : public Tank
	{
	public:
		TankPlayer();
		~TankPlayer() override;

		void Update() override;

		void Fire() override;

		void EventHandler(Event::Event& event) override;
	};
}
