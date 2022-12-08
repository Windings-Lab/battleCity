#pragma once
#include "Tank.h"

namespace BattleCity::Object
{
	class TankNPC : public Tank
	{
	public:
		TankNPC();

		void Fire() override;
		void Update() override;
	};
}


