#pragma once

#include "SpriteAliases.h"

namespace BattleCity::Sprite
{
	class Sprite;

	class Texture final
	{
	public:
		Texture(Sprite&, const TextureSize&);
		DISALLOW_COPY_MOVE(Texture)
		~Texture();

		void DrawAt(X, Y)  const noexcept;
		const TextureSize& GetSize() const noexcept;

	private:
		Sprite* mTexture;
		TextureSize mSpriteSize;
	};
}


