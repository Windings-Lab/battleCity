#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class PowerUp : public Object
	{
    public:
		using Object::Object;

		void Update() override;

	private:
		void InitializeComponents() override;
	};
}

