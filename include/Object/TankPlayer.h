#pragma once

#include "Event.h"
#include "Tank.h"

namespace BattleCity
{
	class TankPlayer final : public Tank
	{
		// Do not use int(4) since framework using it for another purpose
		// Look at FRKey
		enum class MovementDirection
		{
			Right,
			Left,
			Down,
			Up,
			Idle = 5
		};
	public:
		TankPlayer();
		~TankPlayer() override;

		void Update(float) override;

		void Fire() override;

		void EventHandler(Event& event) override;
	};
}
