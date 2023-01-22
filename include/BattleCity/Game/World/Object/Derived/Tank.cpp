#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Tank::Tank()
		: Object()
		, mTexture(AddComponent<Component::Texture>(*this))
		, mCollider(AddComponent<Component::Collider>(*this))
		, mMovable(AddComponent<Component::Movable>(*this))
		, mFireable(AddComponent<Component::Fireable>(*this))
	{}

    void Tank::Update()
    {
        mCollider->UpdateOldCollider();

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
            if (oldRectangle.GetX() + oldRectangle.GetWidth() <= oldOtherRectangle.GetX())
            {
                SetX(rectangle.GetPosition().X + penetration.X);
                mMovable->StopMovement();
            }
            break;
        case Direction::Left:
            if(oldRectangle.GetX() >= oldOtherRectangle.GetX() + oldOtherRectangle.GetWidth())
            {
                SetX(rectangle.GetPosition().X + penetration.X);
                mMovable->StopMovement();
            }
            break;
        case Direction::Down:
            if (oldRectangle.GetY() + oldRectangle.GetHeight() <= oldOtherRectangle.GetY())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
                mMovable->StopMovement();
            }
            break;
        case Direction::Up:
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
}
