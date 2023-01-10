#include "PCHeader.h"

#include "Tank.h"

#include "BattleCity/Game/World/Object/Components/Fireable.h"
#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
    void Tank::OnComponentAdd()
    {
        mFireable = GetComponent<Component::Fireable>();
        mMovable = GetComponent<Component::Movable>();
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
