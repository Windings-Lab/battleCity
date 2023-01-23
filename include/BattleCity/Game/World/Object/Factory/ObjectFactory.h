#pragma once

#include "BattleCity/Game/World/Object/ObjectAliases.h"

namespace BattleCity::Engine::Physics
{
	class Rectangle;
}

namespace BattleCity::Engine::Texture
{
	class GroupLibrary;
}

namespace BattleCity::Game::World
{
	class Map;
}

namespace BattleCity::Game::World::Object
{
	class GameOver;
	class Observer;
	class QuadTree;

	class Explosion;
	class Phoenix;
	class Wall;
	class PowerUp;
	class Bullet;
	class Tank;
	class Background;
	class Object;
}

namespace BattleCity::Game::World::Object::Factory
{
	struct Factory
	{
		explicit Factory(Map&, QuadTree&, const Engine::Texture::GroupLibrary&);

		DISALLOW_COPY_MOVE(Factory)

		virtual ~Factory() = default;

		virtual std::shared_ptr<Background> CreateBackgrounds(Position = {0, 0}) = 0;

		virtual std::shared_ptr<GameOver> CreateGameOver(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Tank> CreateTank(Type tankType, Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Bullet> CreateBullet(Position, Direction) = 0;

		virtual std::shared_ptr<PowerUp> CreatePowerUp(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Wall> CreateWall(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Phoenix> CreatePhoenix(Position = { 0, 0 }) = 0;

		virtual std::shared_ptr<Explosion> CreateExplosion(ExplosionType, Position = { 0, 0 }) = 0;

	protected:
		std::function<void(std::shared_ptr<Object>, Layer)> mInsertToMap;
		std::function<void(ID, Layer)> mObjectDestroyer;

		const Engine::Physics::Rectangle& mScreenBounds;
		const Engine::Physics::Rectangle& mWorldBounds;

		std::function<void(const Object*)> mInsertToQuadTree;
		Observer& mQuadTreeObserver;

		const Engine::Texture::GroupLibrary& mTextureGroups;
	};
}


