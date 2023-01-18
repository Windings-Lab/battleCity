#include "PCHeader.h"

#include "Tank.h"

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
        SetPreviousPosition(GetPosition());
        SetPosition(GetPosition() + mMovable->GetSpeed());
        NotifyObjectUpdated(*this);
    }

    void Tank::ResolveCollisions(const Object* object)
    {
	    Object::ResolveCollisions(object);
        StopMovement();
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
