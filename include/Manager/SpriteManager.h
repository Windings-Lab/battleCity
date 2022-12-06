#pragma once

#include "Framework.h"
#include "Manager.h"
#include "Object.h"

namespace BattleCity::Manager
{
	class SpriteManager final : public Manager
	{
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

		using SpriteObjectBehaviour = std::unordered_map<Object::Behaviour, SpriteObject>;
		using SpriteAtlas = std::unordered_map<SpriteType, SpriteObjectBehaviour>;
	public:
		static SpriteManager& GetInstance();

		SpriteManager(const SpriteManager&) = delete;
		SpriteManager(SpriteManager&&) = delete;

		SpriteManager& operator=(const SpriteManager&) = delete;
		SpriteManager& operator=(SpriteManager&&) = delete;

		~SpriteManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		const Sprite* GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour) const;
		void SetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour);

	private:
		SpriteManager();

		SpriteAtlas mSpriteAtlas;
	};
}
