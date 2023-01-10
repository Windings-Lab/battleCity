#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    void Tank::OnComponentAdd()
    {
        mFireable = GetComponent<Component::Fireable>();
        mMovable = GetComponent<Component::Movable>();
        mCollider = GetComponent<Component::Collider>();
    }

    void Tank::Update()
    {
        mCollider->SetPreviousPosition(GetPosition());
        SetPosition(GetPosition() + mMovable->GetSpeed());
        mCollider->Update(GetPosition(), GetSize());
    }

    void Tank::Fire()
    {
        mFireable->Fire(GetBulletSpawnPosition(), mMovable->GetDirection());
    }

    Position Tank::GetBulletSpawnPosition() const noexcept
    {
	    const Size tankSize = GetSize();

        Position bulletPosition(GetPosition());
        bulletPosition.X += tankSize.X / 2;

        return bulletPosition;
    }
}
