#include "PCHeader.h"
#include "Bullet.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Health.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Bullet::Bullet()
		: Object()
		, mTexture(AddComponent<Component::Texture>(*this))
		, mMovable(AddComponent<Component::Movable>(*this))
		, mCollider(AddComponent<Component::Collider>(*this))
	{}

    void Bullet::Update()
    {
		SetPosition(GetPosition() + mMovable->GetVelocity());

        Object::Update();
    }
    void Bullet::ResolveCollisions(Object& object)
    {
		auto healthComponent = object.GetComponent<Component::Health>();
		if(healthComponent)
		{
			healthComponent->SetHealth(healthComponent->GetHealth() - 1);
		}

		MarkForDestroy();
    }

    void Bullet::OnOutOfBounds(const Vector2Int&)
    {
		MarkForDestroy();
    }

    void Bullet::AdjustPositionToDirection()
    {
		const Size& textureSize = mTexture->GetSize();
		const Size textureHalfSize = textureSize / 2;

		switch (mMovable->GetMovementDirection())
		{
		case Direction::Right:
			SetY(GetPosition().Y - textureHalfSize.Y);
			break;
		case Direction::Left:
			SetY(GetPosition().Y - textureHalfSize.Y);
			SetX(GetPosition().X - textureSize.X);
			break;
		case Direction::Down:
			SetX(GetPosition().X - textureHalfSize.X);
			break;
		case Direction::Up:
			SetX(GetPosition().X - textureHalfSize.X);
			SetY(GetPosition().Y - textureSize.Y);
			break;
		}
    }
}
