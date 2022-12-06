#pragma once

#include <memory>
#include <unordered_map>

#include "Framework.h"
#include "Manager.h"

namespace BattleCity::Manager
{
	class SpriteManager final : public Manager
	{
		enum class SpriteBehaviour;
		enum class SpriteType;

		using SpriteAtlas = std::unordered_map<SpriteType, std::unordered_map<SpriteBehaviour, SpriteObject>>;
	public:
		enum class SpriteBehaviour
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

		enum class SpriteType
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
	};
}
