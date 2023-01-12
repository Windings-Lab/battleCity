#include "PCHeader.h"

#include "Wall.h"

#include "BattleCity/Game/World/Object/Components/Collider.h"

namespace BattleCity::Game::World::Object
{
	void Wall::OnComponentInitialization()
	{
		mCollider = GetComponent<Component::Collider>();
	}

	void Wall::Update()
	{
		mCollider->Update(GetPosition(), GetSize());
	}
}
