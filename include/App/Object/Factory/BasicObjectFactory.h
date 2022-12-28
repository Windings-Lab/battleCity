#pragma once
#include "Object.h"

namespace BattleCity::Object
{
	struct BasicObjectFactory : Object::Factory
	{
	private:
		BasicObjectFactory() = default;

	public:
		static BasicObjectFactory& GetInstance();

		Object* const CreateWorldBoundaries() override;

		Object* const CreateTank(Type tankType) override;

		Object* const CreateBullet() override;

		Object* const CreatePowerUp() override;

		Object* const CreateWall() override;

		Object* const CreatePhoenix() override;

		Object* const CreateExplosion() override;
	};
}
