#pragma once

#include "Texture.h"
#include "SpriteAliases.h"

namespace BattleCity::Sprite
{
	using TextureContainer = std::unordered_map<TextureType, Texture>;

	class BCSprite final
	{
	private:
		friend void swap(BCSprite&, BCSprite&) noexcept;

	private:
		BCSprite();

	public:
		explicit BCSprite(TextureContainer&);

		DISALLOW_COPY(BCSprite)
		ALLOW_MOVE(BCSprite)

		~BCSprite() = default;

		void DrawAt(X, Y)  const noexcept;
		const TextureSize& GetSize() const noexcept;

		void ChangeTexture(TextureType);

	private:
		Texture* mCurrentTexture;
		TextureContainer mSpriteContainer;
	};
}
