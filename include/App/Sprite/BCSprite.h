#pragma once

namespace BattleCity::Sprite
{
	class Texture;

	class BCSprite final
	{
	private:
		friend void swap(BCSprite& first, BCSprite& second) noexcept;

	private:
		using X = int;
		using Y = int;
		using TextureSize = Vector2Int;
		using SpriteContainer = std::unordered_map<TextureType, Texture>;

	private:
		BCSprite();

	public:
		explicit BCSprite(SpriteContainer&);

		DISALLOW_COPY(BCSprite)
		ALLOW_MOVE(BCSprite)

		~BCSprite() = default;

		void DrawAt(X, Y)  const noexcept;
		const TextureSize& GetSpriteSize() const noexcept;

		void ChangeTexture(TextureType);

	private:
		Texture* mCurrentTexture;

		SpriteContainer mSpriteContainer;
	};
}
