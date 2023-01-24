#include "PCHeader.h"
#include "Bullet.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Explodable.h"
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
		, mExplodable(AddComponent<Component::Explodable>(*this))
		, mIgnoreColliderType(Type::Error)
	{}

    void Bullet::Update()
    {
		SetPosition(GetPosition() + mMovable->GetVelocity());

        Object::Update();
    }
    void Bullet::ResolveCollisions(Object& object)
    {
		auto otherCollider = object.GetComponent<Component::Collider>();
		if((!otherCollider->IsSolid() 
		|| otherCollider->GetColliderType() == mIgnoreColliderType)
		&& otherCollider->GetColliderType() != mCollider->GetColliderType()) return;

		auto healthComponent = object.GetComponent<Component::Health>();
		if(healthComponent)
		{
			if(mIgnoreColliderType == Type::TankPlayer 
			&& otherCollider->GetColliderType() == Type::Phoenix) return;

			healthComponent->SetHealth(healthComponent->GetHealth() - 1);
		}

		MarkForDestroy();
    }

    void Bullet::OnOutOfBounds(const Vector2Int&)
    {
		MarkForDestroy();
    }

    void Bullet::OnDestroy()
    {
		mExplodable->Explode(ExplosionType::Small);
	    Object::OnDestroy();
    }

    void Bullet::SetIgnoreColliderType(Type type) noexcept
    {
		mIgnoreColliderType = type;
    }

    void Bullet::AdjustPositionToDirection()
    {
		const Size& colliderSize = mCollider->GetSize();
		const Size colliderHalfSize = colliderSize / 2;

		switch (mMovable->GetMovementDirection())
		{
		case Direction::Right:
			SetY(GetPosition().Y - colliderHalfSize.Y);
			break;
		case Direction::Left:
			SetY(GetPosition().Y - colliderHalfSize.Y);
			SetX(GetPosition().X - colliderSize.X);
			break;
		case Direction::Down:
			SetX(GetPosition().X - colliderHalfSize.X);
			break;
		case Direction::Up:
			SetX(GetPosition().X - colliderHalfSize.X);
			SetY(GetPosition().Y - colliderSize.Y);
			break;
		}

		mCollider->UpdateCollider();
    }
}
