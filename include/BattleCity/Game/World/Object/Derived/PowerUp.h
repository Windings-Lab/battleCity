#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	// Abstract
	class PowerUp : public Object
	{
    public:
		explicit PowerUp(const std::function<void(ID, Layer)>&);
	};
}

