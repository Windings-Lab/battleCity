#pragma once
#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Pixel : public Object
	{
	public:
		using Object::Object;

		void InitializeComponents() override;

		void Update() override;
	};
}


