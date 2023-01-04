#pragma once

namespace BattleCity::Framework
{
	class Sprite;

	class Texture final
	{
	private:
		friend void swap(Texture&, Texture&) noexcept;

	private:
		Texture();

	public:
		Texture(const char*);

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

