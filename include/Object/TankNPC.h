#pragma once
#include "Tank.h"

namespace BattleCity::Object
{
	class TankNPC : public Tank
	{
	public:
		TankNPC(int x, int y);

		void Fire() override;
		void Update() override;
	};
}


