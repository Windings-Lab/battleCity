#pragma once

#include "BattleCity/Game/World/Object/Object.h"

namespace BattleCity::Game::World::Object
{
	namespace Component
	{
		class Collider;
		class Texture;
	}

	class GameOver : public Object
	{
	public:
		explicit GameOver(const Position&, const std::function<void(ID, Layer)>&);

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;

		void SetEndAnimationPosition(Position) noexcept;

	private:
		Component::Texture* mTexture;
		Component::Collider* mCollider;

		Position mEndAnimationPosition;
	};
}


