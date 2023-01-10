#include "PCHeader.h"
#include "Bullet.h"

#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    void Bullet::OnComponentAdd()
    {
        mMovable = GetComponent<Component::Movable>();
        mCollider = GetComponent<Component::Collider>();
    }

    void Bullet::Update()
    {
        mCollider->SetPreviousPosition(GetPosition());
        SetPosition(GetPosition() + mMovable->GetSpeed());
        mCollider->Update(GetPosition(), GetSize());
    }
}
