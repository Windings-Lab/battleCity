#pragma once

#include <memory>
#include <unordered_map>

#include "Framework.h"
#include "Manager.h"
#include "Object.h"

namespace BattleCity::Manager
{
	enum class SpriteType;
	enum class SpriteObjects;

	//using SpriteAtlas = std::unordered_map<SpriteObjects, std::unordered_map<SpriteType, std::unique_ptr<Sprite>>>;

	class SpriteManager final : public Manager
	{
		enum class SpriteType
		{
			Error,
			Basic,
			Down,
			Left,
			Right,
			Up,
			ExplosionL1,
			ExplosionL2,
			ExplosionS1,
			ExplosionS2,
			ExplosionS3
		};

		enum class SpriteObjects
		{
			Error,
			TankPlayer = static_cast<int>(Object::Type::TankPlayer),
			Tank = static_cast<int>(Object::Type::Tank),
			Bullet = static_cast<int>(Object::Type::Bullet),
			Wall = static_cast<int>(Object::Type::Wall),
			Explosion = static_cast<int>(Object::Type::Explosion),
			PowerUp = static_cast<int>(Object::Type::PowerUp),
			Phoenix,
			Flag,
			Background,
			GameOverLogo
		};
	public:
		static SpriteManager& GetInstance();

		SpriteManager(const SpriteManager&) = delete;
		SpriteManager(SpriteManager&&) = delete;

		SpriteManager& operator=(const SpriteManager&) = delete;
		SpriteManager& operator=(SpriteManager&&) = delete;

		~SpriteManager() override = default;

		void StartUp() override;
		void ShutDown() override;

	private:
		SpriteManager();

		//SpriteAtlas mSpriteAtlas;
	};
}
