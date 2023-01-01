#pragma once

#include "SpriteBuilder.h"

namespace BattleCity
{
	class WorldMap;
}

namespace BattleCity::Object
{
	class Object;

	struct ObjectFactory
	{
		explicit ObjectFactory(WorldMap& inserter) : mInserter(inserter) {}

		DISALLOW_COPY_MOVE(ObjectFactory)

		virtual ~ObjectFactory() = default;

		virtual Object* CreateWorldBoundaries() = 0;

		virtual Object* CreateTank(Type tankType) = 0;

		virtual Object* CreateBullet() = 0;

		virtual Object* CreatePowerUp() = 0;

		virtual Object* CreateWall() = 0;

		virtual Object* CreatePhoenix() = 0;

		virtual Object* CreateExplosion() = 0;

	protected:
		WorldMap& mInserter;
		Sprite::SpriteBuilder mSpriteBuilder;
	};
}


