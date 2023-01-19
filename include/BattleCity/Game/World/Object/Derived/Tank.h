#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	class Bullet;

	namespace Component
	{
		class Movable;
		class Fireable;
	}

	class Tank : public Object
	{
	public:
		using Object::Object;

		void InitializeComponents() override;

		void Update() override;
		void ResolveCollisions(const Object*, const Vector2Int&) override;

		void Fire();

		void SetBullet(const std::function<std::shared_ptr<Bullet>(Position)>&);

		void SetSpeed(Speed) noexcept;
		void SetDirection(MovementDirection) noexcept;
		void StopMovement() noexcept;

	private:
		Component::Fireable* mFireable;
		Component::Movable* mMovable;
	};
}
