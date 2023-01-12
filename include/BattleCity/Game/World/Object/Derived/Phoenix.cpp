#include "PCHeader.h"

#include "Phoenix.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
    void Phoenix::OnComponentInitialization()
    {
        mCollider = GetComponent<Component::Collider>();
    }

    void Phoenix::Update()
    {
        mCollider->Update(GetPosition(), GetSize());
    }
}
