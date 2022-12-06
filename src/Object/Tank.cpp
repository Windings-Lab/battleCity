#include "PCHeader.h"

#include "Tank.h"

#include "Explosion.h"
#include "GameManager.h"
#include "WorldManager.h"

namespace BattleCity
{
	Tank::Tank(Type type) : Object(type) {	}

	Tank::~Tank()
	{
		if(Manager::GM.GetGameOver()) return; // TODO: Fix

		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(true);
		newExp->SetPosition(X(), Y());

		Manager::WM.InsertObject(newExp);
	}
}
