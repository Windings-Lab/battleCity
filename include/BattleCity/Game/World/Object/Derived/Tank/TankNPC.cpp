#include "PCHeader.h"
#include "TankNPC.h"

#include "BattleCity/Game/World/Object/Components/Movable.h"

namespace BattleCity::Game::World::Object
{
	void TankNPC::ResolveCollisions(Object& object)
	{
		Tank::ResolveCollisions(object);
		mMovable->SetMovementDirection(mMovable->GetMovementDirection());
	}
}

