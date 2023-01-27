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
		explicit GameOver(const Position&, const Position&, const std::function<void(ID, Layer)>&);

		void Update() override;
		void ResolveCollisions(Object&) override;
		void OnOutOfBounds(const Vector2Int&) override;

	private:
		Component::Texture* mTexture;
		Component::Collider* mCollider;

		Position mEndAnimationPosition;
	};
}


