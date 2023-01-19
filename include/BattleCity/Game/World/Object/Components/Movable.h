#pragma once
#include "Component.h"

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

namespace BattleCity::Game::World::Object::Component
{
	class Movable : public Component
	{
	public:
		using Component::Component;
		~Movable() override = default;

		Movable& SetSpeed(Speed) noexcept;
		Vector2Int GetSpeed() const noexcept;

		Movable& SetDirection(MovementDirection) noexcept;
		MovementDirection GetDirection() const noexcept;

		void StopMovement() noexcept;

	private:
		Speed mSpeed = 0;
		Velocity mVelocity;

		MovementDirection mDirection;
	};
}
