#pragma once

#include "Tank.h"

namespace BattleCity::Object
{
	class TankPlayer final : public Tank
	{
	public:
		TankPlayer(int x, int y);
		~TankPlayer() override;

		void Update() override;

		void Fire() override;
	};
}
