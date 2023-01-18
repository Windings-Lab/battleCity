#include "PCHeader.h"
#include "Bullet.h"

#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::InitializeComponents()
    {
        Object::InitializeComponents();

        mMovable = AddComponent<Component::Movable>(*this);
    }

    void Bullet::Update()
    {
        Object::Update();

        SetPosition(GetPosition() + mMovable->GetSpeed());
    }

    void Bullet::SetDirection(MovementDirection direction) noexcept
    {
        mMovable->SetDirection(direction);
    }
}
