#pragma once
#include "Component.h"

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object::Component
{
	class Movable : public Component
	{
	public:
		Movable();
		~Movable() override = default;

		Vector2Int GetSpeedDirection() const noexcept;

		void SetSpeed(Speed) noexcept;

		void SetDirection(Direction) noexcept;
		const Direction& GetDirection() const noexcept;

	private:
		int mSpeed;
		Direction mDirection;
	};
}
