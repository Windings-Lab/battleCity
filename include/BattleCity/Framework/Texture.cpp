#include "PCHeader.h"
#include "Texture.h"

namespace BattleCity::Framework
{
	namespace
	{
		FRAMEWORK_API Sprite* createSprite(const char* path);
		FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
		FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
		FRAMEWORK_API void destroySprite(Sprite* s);
	}

	void swap(Texture& f, Texture& s) noexcept
	{
		using std::swap;

		swap(f.mTexture, s.mTexture);
		swap(f.mWidth, s.mWidth);
		swap(f.mHeight, s.mHeight);
	}

	Texture::Texture()
		: mTexture(nullptr)
		, mWidth(0)
		, mHeight(0)
	{}

	Texture::Texture(const char* path)
		: mTexture(createSprite(path))
	{
		getSpriteSize(mTexture, mWidth, mHeight);
	}

	Texture::Texture(Texture&& mve) noexcept : Texture()
	{
		swap(*this, mve);
	}

	Texture& Texture::operator=(Texture&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	Texture::~Texture()
	{
		if(mTexture)
		{
			destroySprite(mTexture);
		}
	}

	void Texture::DrawAt(int x, int y) const noexcept
	{
		drawSprite(mTexture, x, y);
	}

	void Texture::GetSize(int& w, int& h) const noexcept
	{
		w = mWidth;
		h = mHeight;
	}
}
