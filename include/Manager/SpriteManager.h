#pragma once

#include "Framework.h"
#include "Manager.h"
#include "Object.h"

namespace BattleCity::Manager
{
	class SpriteManager final : public Manager
	{
		enum class SpriteType;

		using SpriteAtlas = std::unordered_map<SpriteType, std::unordered_map<Object::Behaviour, SpriteObject>>;
	public:
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
