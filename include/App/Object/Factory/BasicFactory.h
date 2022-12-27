#pragma once
#include "Object.h"

namespace BattleCity::Object
{
	struct BasicFactory : Object::Factory
	{
	private:
		BasicFactory() = default;

	public:
		static BasicFactory& GetInstance();

		Object* const CreateWorldBoundaries() override;

		Object* const CreateTank(Type tankType) override;

		Object* const CreateBullet() override;

		Object* const CreatePowerUp() override;

		Object* const CreateWall() override;

		Object* const CreatePhoenix() override;

		Object* const CreateExplosion() override;
	};
}
