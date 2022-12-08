#pragma once

#include "Event.h"
#include "Tank.h"

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
