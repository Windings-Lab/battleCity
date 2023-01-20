#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Engine/Physics/Rectangle.h"
#include "BattleCity/Framework/Texture.h"
#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
    void Tank::InitializeComponents()
    {
        Object::InitializeComponents();

        mFireable = AddComponent<Component::Fireable>(*this);
        mMovable = AddComponent<Component::Movable>(*this);
    }

    void Tank::Update()
    {
        SetPosition(GetPosition() + mMovable->GetSpeed());

        Object::Update();
    }

    void Tank::ResolveCollisions(const Object* other)
    {
        auto penetration = GetBounds().GetPenetration(other->GetBounds());

        switch (mMovable->GetDirection())
        {
        case MovementDirection::Right:
            SetX(GetBounds().GetPosition().X + penetration.X);
            break;
        case MovementDirection::Left:
            SetX(GetBounds().GetPosition().X + penetration.X);
            break;
        case MovementDirection::Down:
            SetY(GetBounds().GetPosition().Y + penetration.Y);
            break;
        case MovementDirection::Up:
            SetY(GetBounds().GetPosition().Y + penetration.Y);
            break;
        }
        StopMovement();

        Object::ResolveCollisions(other);
    }

    void Tank::Fire()
    {
        mFireable->Fire();
    }
    void Tank::SetBullet(const std::function<std::shared_ptr<Bullet>(Position)>& bullet)
    {
        mFireable->SetBullet(bullet);
    }

    void Tank::SetSpeed(Speed num) noexcept
    {
        mMovable->SetSpeed(num);
    }
    void Tank::SetDirection(MovementDirection direction) noexcept
    {
        mMovable->SetDirection(direction);
        switch (direction)
        {
        case MovementDirection::Right:
            ChangeTextureTo(Framework::TextureType::Right);
            break;
        case MovementDirection::Left: 
            ChangeTextureTo(Framework::TextureType::Left);
            break;
        case MovementDirection::Down: 
            ChangeTextureTo(Framework::TextureType::Down);
            break;
        case MovementDirection::Up: 
            ChangeTextureTo(Framework::TextureType::Up);
            break;
        default: ;
        }
    }
    void Tank::StopMovement() noexcept
    {
        mMovable->StopMovement();
    }
}
