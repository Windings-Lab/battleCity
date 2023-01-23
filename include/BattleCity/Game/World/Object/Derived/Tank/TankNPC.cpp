#include "PCHeader.h"
#include "TankNPC.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
	void TankNPC::ResolveCollisions(Object& other)
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
            }
            break;
        case Direction::Left:
            // If Collision on Left
            if (oldRectangle.GetX() >= oldOtherRectangle.GetX() + oldOtherRectangle.GetWidth())
            {
                SetX(rectangle.GetPosition().X + penetration.X);
            }
            break;
        case Direction::Down:
            // If Collision on Down
            if (oldRectangle.GetY() + oldRectangle.GetHeight() <= oldOtherRectangle.GetY())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
            }
            break;
        case Direction::Up:
            // If Collision on Up
            if (oldRectangle.GetY() >= oldOtherRectangle.GetY() + oldOtherRectangle.GetHeight())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
            }
            break;
        }

        Object::ResolveCollisions(other);
	}
}

