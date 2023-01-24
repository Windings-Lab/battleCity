#pragma once
#include "Component.h"

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Framework
{
	enum class TextureType;
}

namespace BattleCity::Game::World::Object::Component
{
	class Collider;
	class Texture;

	class Movable : public Component
	{
	public:
		explicit Movable(Object&);
		~Movable() override = default;

		void SetSpeed(Speed) noexcept;
		const Velocity& GetVelocity() const noexcept;

		void SetMovementDirection(Direction) noexcept;
		Direction GetMovementDirection() const noexcept;

		void StopMovement() noexcept;
		bool IsMoving() const noexcept;

	private:
		Collider* mCollider;
		Texture* mTexture;

		Speed mSpeed = 0;
		Velocity mVelocity;
		bool mMoving;

		Direction mMovementDirection;
	};
}
