#pragma once

#include "Texture/Texture.h"

namespace BattleCity::Sprite
{
	using TextureContainer = std::unordered_map<Texture::Type, Texture::Texture>;

	class BCSprite final
	{
	private:
		friend void swap(BCSprite&, BCSprite&) noexcept;
		friend class Builder;

	private:
		BCSprite();

	public:
		explicit BCSprite(TextureContainer&);

		DISALLOW_COPY(BCSprite)
		ALLOW_MOVE(BCSprite)

		~BCSprite();

		void DrawAt(X, Y)  const noexcept;
		const Texture::Size& GetSize() const noexcept;

		void ChangeTexture(Texture::Type);

	private:
		Texture::Texture* mCurrentTexture;
		TextureContainer mSpriteContainer;

	};
}
