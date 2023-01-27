#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"
#include "BattleCity/Game/World/Object/Components/Explodable.h"
#include "BattleCity/Game/World/Object/Components/Health.h"

namespace BattleCity::Game::World::Object
{
	Tank::Tank(const std::function<void(ID, Layer)>& d)
		: Object(d)
		, mTexture(AddComponent<Component::Texture>())
		, mCollider(AddComponent<Component::Collider>())
		, mMovable(AddComponent<Component::Movable>())
		, mFireable(AddComponent<Component::Fireable>())
		, mExplodable(AddComponent<Component::Explodable>())
		, mHealth(AddComponent<Component::Health>())
	{}

    void Tank::Update()
    {
        if (mHealth->GetHealth() <= 0)
        {
            MarkForDestroy();
            return;
        }

        SetPosition(GetPosition() + mMovable->GetVelocity());

        Object::Update();
    }

    void Tank::ResolveCollisions(Object& other)
    {
        if (!mMovable->IsMoving()) return;
        auto otherCollider = other.GetComponent<Component::Collider>();
        auto otherMovable = other.GetComponent<Component::Movable>();
        if (!otherCollider->IsSolid() || !otherMovable) return;

        auto& rectangle = mCollider->GetRectangle();
        auto& otherRectangle = otherCollider->GetRectangle();
        auto& oldRectangle = mCollider->GetOldRectangle();
        auto& oldOtherRectangle = otherCollider->GetOldRectangle();

        auto penetration = rectangle.GetPenetration(otherRectangle);

        auto movementDirection = mMovable->GetMovementDirection();

        switch (movementDirection)
        {
        case Direction::Right:
            // If Collision on Right
            if (oldRectangle.GetX() + oldRectangle.GetWidth() <= oldOtherRectangle.GetX())
            {
                SetX(rectangle.GetPosition().X + penetration.X);
                mMovable->StopMovement();
            }
            break;
        case Direction::Left:
            // If Collision on Left
            if(oldRectangle.GetX() >= oldOtherRectangle.GetX() + oldOtherRectangle.GetWidth())
            {
                SetX(rectangle.GetPosition().X + penetration.X);
                mMovable->StopMovement();
            }
            break;
        case Direction::Down:
            // If Collision on Down
            if (oldRectangle.GetY() + oldRectangle.GetHeight() <= oldOtherRectangle.GetY())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
                mMovable->StopMovement();
            }
            break;
        case Direction::Up:
            // If Collision on Up
            if (oldRectangle.GetY() >= oldOtherRectangle.GetY() + oldOtherRectangle.GetHeight())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
                mMovable->StopMovement();
            }
            break;
        }

        Object::ResolveCollisions(other);
    }

    void Tank::OnOutOfBounds(const Vector2Int& penetration)
    {
        auto& rectangle = mCollider->GetRectangle();

        switch (mMovable->GetMovementDirection())
        {
        case Direction::Right:
        case Direction::Left:
            SetX(rectangle.GetPosition().X + penetration.X);
            break;
        case Direction::Down:
        case Direction::Up:
            SetY(rectangle.GetPosition().Y + penetration.Y);
            break;
        }
        mMovable->StopMovement();

        Object::OnOutOfBounds(penetration);
    }

    void Tank::OnDestroy()
    {
        mExplodable->Explode(ExplosionType::Large);
	    Object::OnDestroy();
    }
}
