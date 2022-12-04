#include "Tank.h"

#include "Explosion.h"
#include "GameManager.h"
#include "WorldManager.h"

#include <memory>

namespace battleCity
{
	Tank::Tank(Type type) : Object(type) {	}

	Tank::~Tank()
	{
		if(GM.GetGameOver()) return; // TODO: Fix

		std::unique_ptr<Object> newExp = std::make_unique<Explosion>(true);
		newExp->SetPosition(X(), Y());

		WM.InsertObject(newExp);
	}
}
