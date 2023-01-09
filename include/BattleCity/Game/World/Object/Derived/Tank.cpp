#include "PCHeader.h"

#include "Tank.h"

namespace BattleCity::Game::World::Object
{
    Position Tank::GetBulletSpawnPosition() const noexcept
    {
        int tankWidth;
        int tankHeight;

        GetTextureSize(tankWidth, tankHeight);

        Position bulletPosition(mPosition);
        bulletPosition.X += tankWidth / 2;

        return bulletPosition;
    }
}
