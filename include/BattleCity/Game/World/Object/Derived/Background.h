#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Background final : public Object
	{
	public:
		explicit Background(const Position&, const std::function<void(ID, Layer)>&);

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;
	};
}
