#pragma once

namespace BattleCity
{
	class WorldMap;
}

namespace BattleCity::Object
{
	class Object;

	struct ObjectAbstractFactory
	{
		explicit ObjectAbstractFactory(WorldMap& inserter) : mInserter(inserter) {}

		DISALLOW_COPY_MOVE(ObjectAbstractFactory)

		virtual ~ObjectAbstractFactory() = default;

		virtual Object* CreateWorldBoundaries(X = 0, Y = 0) = 0;

		virtual Object* CreateTank(Type tankType, X = 0, Y = 0) = 0;

		virtual Object* CreateBullet(X = 0, Y = 0) = 0;

		virtual Object* CreatePowerUp(X = 0, Y = 0) = 0;

		virtual Object* CreateWall(X = 0, Y = 0) = 0;

		virtual Object* CreatePhoenix(X = 0, Y = 0) = 0;

		virtual Object* CreateExplosion(X = 0, Y = 0) = 0;

	protected:
		WorldMap& mInserter;
	};
}


