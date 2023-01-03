#pragma once

#include "Framework/Texture/Aliases.h"

namespace BattleCity::Framework::Texture
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

		void DrawAt(int, int)  const noexcept;
		void GetSize(int&, int&) const noexcept;

	private:
		Sprite* mTexture;
		int mWidth;
		int mHeight;
	};
}


