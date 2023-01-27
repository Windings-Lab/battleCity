#include "PCHeader.h"
#include "TankNPC.h"

#include "BattleCity/Game/World/Object/Components/AI.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
	TankNPC::TankNPC(const std::function<void(ID, Layer)>& d)
		: Tank(d)
		, mAi(AddComponent<Component::AI>())
	{
	}

	void TankNPC::Update()
	{
		Tank::Update();
        mAi->Update();
	}

	void TankNPC::ResolveCollisions(Object& other)
	{
        if (!mMovable->IsMoving()) return;
        auto otherCollider = other.GetComponent<Component::Collider>();
        auto otherMovable = other.GetComponent<Component::Movable>();
        if (!otherCollider->IsSolid() 
        || !otherMovable) return;

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
                mAi->RandomChangeDirection();
            }
            break;
        case Direction::Left:
            // If Collision on Left
            if (oldRectangle.GetX() >= oldOtherRectangle.GetX() + oldOtherRectangle.GetWidth())
            {
                SetX(rectangle.GetPosition().X + penetration.X);
                mAi->RandomChangeDirection();
            }
            break;
        case Direction::Down:
            // If Collision on Down
            if (oldRectangle.GetY() + oldRectangle.GetHeight() <= oldOtherRectangle.GetY())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
                mAi->RandomChangeDirection();
            }
            break;
        case Direction::Up:
            // If Collision on Up
            if (oldRectangle.GetY() >= oldOtherRectangle.GetY() + oldOtherRectangle.GetHeight())
            {
                SetY(rectangle.GetPosition().Y + penetration.Y);
                mAi->RandomChangeDirection();
            }
            break;
        }

        Object::ResolveCollisions(other);
	}

	void TankNPC::OnOutOfBounds(const Vector2Int& vector2Int)
	{
		Tank::OnOutOfBounds(vector2Int);
        mAi->RandomChangeDirection();
	}
}

