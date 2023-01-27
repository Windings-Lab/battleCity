#include "PCHeader.h"
#include "GameOver.h"

#include "BattleCity/Game/World/Object/Components/TextureComponent.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
	GameOver::GameOver(const std::function<void(ID, Layer)>& d)
		: Object(d)
		, mTexture(AddComponent<Component::Texture>())
		, mCollider(AddComponent<Component::Collider>())
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

	void GameOver::SetEndAnimationPosition(Position position) noexcept
	{
		mEndAnimationPosition = position;
	}
}
