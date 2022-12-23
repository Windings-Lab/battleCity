#pragma once

#include "Manager.h"
#include "Rectangle.h"

class Sprite;

namespace BattleCity::Manager
{
	namespace 
	{
		FRAMEWORK_API Sprite* createSprite(const char* path);
		FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
		FRAMEWORK_API void destroySprite(Sprite* s);
		FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
	}

	class SpriteManager final : public Manager
	{
	public:
		static SpriteManager& GetInstance();

		static void DrawSprite(const Sprite*, int w, int h);
		static Rectangle GetSpriteRectangle(const Sprite* sprite, int x = 0, int y = 0);
	private:
		SpriteManager();
	public:
		SpriteManager(const SpriteManager&) = delete;
		SpriteManager(SpriteManager&&) = delete;

		SpriteManager& operator=(const SpriteManager&) = delete;
		SpriteManager& operator=(SpriteManager&&) = delete;

		~SpriteManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		Sprite* SetAndGetSprite(const SpriteBehaviour& spriteBehaviour);
	private:
		Sprite* SetSprite(const SpriteBehaviour& spriteBehaviour);

	private:
		struct SpriteDeleter;
		using SpriteObject = std::unique_ptr<Sprite, SpriteDeleter>;
		using SpriteAtlas = std::unordered_map<SpriteBehaviour, SpriteObject>;

		SpriteAtlas mSpriteAtlas;
	};

	struct SpriteManager::SpriteDeleter
	{
		SpriteDeleter() = default;
		SpriteDeleter(const SpriteDeleter&) = delete;
		SpriteDeleter(SpriteDeleter&&) noexcept = delete;

		SpriteDeleter& operator=(const SpriteDeleter&) = delete;
		SpriteDeleter& operator=(SpriteDeleter&&) noexcept = delete;

		~SpriteDeleter() = default;

		void operator()(const Sprite* p) const
		{
			destroySprite(const_cast<Sprite*>(p));
		}
	};

	constexpr auto& SM = SpriteManager::GetInstance;
}
