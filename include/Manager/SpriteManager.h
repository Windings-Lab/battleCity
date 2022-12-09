#pragma once

#include "Framework.h"
#include "Manager.h"
#include "Rectangle.h"

namespace BattleCity::Manager
{
	class SpriteManager final : public Manager
	{
	public:
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

		void DrawSprite(const Sprite*, const int& w, const int& h) const;

		const Sprite* SetAndGetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour);
		Rectangle GetSpriteRectangle(const Sprite* sprite, int x = 0, int y = 0) const;

	private:
		const Sprite* GetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour) const;
		const Sprite* SetSprite(SpriteType spriteType, Object::Behaviour objectBehaviour);
	private:
		SpriteManager();

		SpriteAtlas mSpriteAtlas;
	};

	inline SpriteManager& SM = SpriteManager::GetInstance();
}
