#pragma once

#include "Rectangle.h"

namespace BattleCity::Sprite
{
	class Sprite;

	class BCSprite final
	{
	public:
		BCSprite();

		BCSprite(const BCSprite&) = delete;
		BCSprite& operator=(const BCSprite&) = delete;

		BCSprite(BCSprite&& mve) noexcept;
		BCSprite& operator=(BCSprite&& mve) noexcept;

		~BCSprite() = default;

		void DrawAt(const Vector2Int& position) const noexcept;
		void DrawAt(int x, int y)  const noexcept;

		void SetSprite(const SpritePair& spriteBehaviour);

		const Vector2Int& GetSpriteSize();

	private:
		void InitSpriteSize();
		friend void swap(BCSprite& first, BCSprite& second) noexcept;

	private:
		struct SpriteDeleter;
		using SpriteObject = std::unique_ptr<Sprite, SpriteDeleter>;
		using SpriteAtlas = std::unordered_map<SpritePair, SpriteObject>;

		static SpriteAtlas mSpriteAtlas;

	private:
		Sprite* mSprite;
		Vector2Int mSpriteSize;
	};
}
