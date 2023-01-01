#pragma once

#include "SpriteAliases.h"

namespace BattleCity::Sprite
{
	class Sprite;

	class Texture final
	{
	private:
		friend void swap(Texture&, Texture&) noexcept;

	private:
		Texture();

	public:
		Texture(Sprite&, const TextureSize&);

		DISALLOW_COPY(Texture)
		ALLOW_MOVE(Texture)

		~Texture();

		static Texture Create(const TexturePath&);

		void DrawAt(X, Y)  const noexcept;
		const TextureSize& GetSize() const noexcept;

	private:
		Sprite* mTexture;
		TextureSize mSpriteSize;
	};
}


