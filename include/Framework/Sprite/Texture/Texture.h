#pragma once

#include "Framework/Sprite/Aliases.h"

namespace BattleCity::Texture
{
	class Sprite;

	class Texture final
	{
	private:
		friend void swap(Texture&, Texture&) noexcept;

	private:
		Texture();

	public:
		Texture(const Path&);
		DISALLOW_COPY(Texture)
		ALLOW_MOVE(Texture)

		~Texture();

		void DrawAt(X, Y)  const noexcept;
		const Size& GetSize() const noexcept;

	private:
		Sprite* mTexture;
		Size mSpriteSize;
	};
}


