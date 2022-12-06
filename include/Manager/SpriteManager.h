#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Framework.h"
#include "Manager.h"

namespace BattleCity::Manager
{
	class SpriteManager final : public Manager
	{
		enum class Behaviour;
		enum class Type;

		using SpriteList = std::unordered_map<Type, std::unordered_map<Behaviour, std::string>>;
		using SpriteAtlas = std::unordered_map<Type, std::unordered_map<Behaviour, SpriteObject>>;

		enum class Behaviour
		{
			Error,
			Basic,
			Down,
			Left,
			Right,
			Up,
			ExplosionSmall1,
			ExplosionSmall2,
			ExplosionSmall3,
			ExplosionLarge1,
			ExplosionLarge2,
		};

		enum class Type
		{
			Error,
			TankPlayer,
			Tank,
			Bullet,
			Wall,
			Explosion,
			PowerUp,
			Phoenix,
			Flag,
			Background,
			GameOver
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

		SpriteAtlas mSpriteAtlas;
		SpriteList mSpriteList;
	};
}
