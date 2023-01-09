#pragma once

#include "BattleCity/Game/World/Object/Object.h"
#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    class Bullet : public Object
    {
    public:
        Bullet(const Engine::Texture::Group&);

        void Update() override;
        void ResolveCollision(const Object&) override;

        void SetPosition(Position) noexcept override;

    private:
        Component::Collider mCollider;
    };
}
