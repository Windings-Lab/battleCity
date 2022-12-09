#pragma once

#include "Manager.h"
#include "Rectangle.h"

struct SpriteDeleter;
class Sprite;
using SpriteObject = std::unique_ptr<const Sprite, SpriteDeleter>;

namespace BattleCity::Manager
{
	FRAMEWORK_API Sprite* createSprite(const char* path);
	FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
	FRAMEWORK_API void destroySprite(Sprite* s);
	FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);

	struct SpriteDeleter
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

	class SpriteManager final : public Manager
	{
		using SpriteAtlas = std::unordered_map<SpriteTypeBehaviourPair, SpriteObject>;
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

	constexpr auto& SM = SpriteManager::GetInstance;
}
