#pragma once
#include "Component.h"

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Game::World::Object::Component
{
	class Movable : public Component
	{
	public:
		using Component::Component;
		~Movable() override = default;

		Movable& SetSpeed(Speed) noexcept;
		Vector2Int GetSpeed() const noexcept;

		Movable& SetDirection(Direction) noexcept;
		const Direction& GetDirection() const noexcept;

	private:
		Speed mSpeed;
		Direction mDirection;
	};
}
