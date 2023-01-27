#include "PCHeader.h"
#include "GameOver.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
	GameOver::GameOver(const Position& endAnimationPos, const Position& pos, const std::function<void(ID, Layer)>& d)
		: Object(pos, d)
		, mTexture(AddComponent<Component::Texture>())
		, mCollider(AddComponent<Component::Collider>())
		, mEndAnimationPosition(endAnimationPos)
	{
	}

	void GameOver::Update()
	{
		// Move animation to center of screen
		if(mCollider->GetRectangle().GetCenter().Y > mEndAnimationPosition.Y)
		{
			SetY(GetPosition().Y - 5);
			mCollider->UpdateCollider();
		}
	}

	void GameOver::ResolveCollisions(Object&)
	{
		// Empty
	}

	void GameOver::OnOutOfBounds(const Vector2Int&)
	{
		// Empty
	}
}
