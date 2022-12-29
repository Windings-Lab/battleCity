#pragma once

#include "Rectangle.h"
#include "SpriteData.h"

namespace BattleCity::Sprite
{
	class Sprite;

	class BCSprite final
	{
	public:
		BCSprite();

		DISALLOW_COPY(BCSprite)

		BCSprite(BCSprite&& mve) noexcept;
		BCSprite& operator=(BCSprite&& mve) noexcept;

		~BCSprite() = default;

		void DrawAt(const Vector2Int& position) const noexcept;
		void DrawAt(int x, int y)  const noexcept;

		void CreateSprite(Object::Type objectType, const std::filesystem::path& spritePath);
		void SetSpriteType(Type spriteBehaviour);

		const Vector2Int& GetSpriteSize();

	private:
		void InitSpriteSize();
		friend void swap(BCSprite& first, BCSprite& second) noexcept;

	private:
		struct SpriteDeleter;

		using SpriteObject = std::unique_ptr<Sprite, SpriteDeleter>;
		using SpriteContainer = std::unordered_map<Type, Sprite*>;
		using SpriteAtlas = std::unordered_map<SpritePair, SpriteObject, SpritePairHash>;

		SpriteContainer mSpriteContainer;
		static SpriteAtlas mSpriteAtlas;

	private:
		Type mType;
		Sprite* mSprite;
		Vector2Int mSpriteSize;

		SpriteData mSpriteData;
	};
}
