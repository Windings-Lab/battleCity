#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/TextureComponent.h"

namespace BattleCity::Game::World::Object
{
	Tank::Tank()
	{
        AddComponent<Component::Texture>(*this);
        AddComponent<Component::Collider>(*this);
        AddComponent<Component::Movable>(*this);
        AddComponent<Component::Fireable>(*this);
	}

    void Tank::Update()
    {
        auto speed = GetComponent<Component::Movable>()->GetSpeed();

        SetPosition(GetPosition() + speed);

        Object::Update();
    }

    void Tank::ResolveCollisions(Object& other)
    {
        auto& rectangle = GetComponent<Component::Collider>()->GetRectangle();
        auto& otherRectangle = other.GetComponent<Component::Collider>()->GetRectangle();
        auto penetration = rectangle.GetPenetration(otherRectangle);

        auto movable = GetComponent<Component::Movable>();

        switch (movable->GetDirection())
        {
        case Direction::Right:
            SetX(rectangle.GetPosition().X + penetration.X);
            break;
        case Direction::Left:
            SetX(rectangle.GetPosition().X + penetration.X);
            break;
        case Direction::Down:
            SetY(rectangle.GetPosition().Y + penetration.Y);
            break;
        case Direction::Up:
            SetY(rectangle.GetPosition().Y + penetration.Y);
            break;
        }
        movable->StopMovement();

        Object::ResolveCollisions(other);
    }

    void Tank::OnOutOfBounds(const Vector2Int& penetration)
    {
        auto& rectangle = GetComponent<Component::Collider>()->GetRectangle();
        auto movable = GetComponent<Component::Movable>();

        switch (movable->GetDirection())
        {
        case Direction::Right:
            SetX(rectangle.GetPosition().X + penetration.X);
            break;
        case Direction::Left:
            SetX(rectangle.GetPosition().X + penetration.X);
            break;
        case Direction::Down:
            SetY(rectangle.GetPosition().Y + penetration.Y);
            break;
        case Direction::Up:
            SetY(rectangle.GetPosition().Y + penetration.Y);
            break;
        }
        movable->StopMovement();

        Object::OnOutOfBounds(penetration);
    }
}
