#include "PCHeader.h"
#include "Texture.h"

namespace BattleCity::Texture
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
		f.mSpriteSize.SetXY(s.mSpriteSize);
		s.mSpriteSize.SetXY(0, 0);
	}

	Texture::Texture() : mTexture(nullptr) {}

	Texture::Texture(const Path& path)
		: mTexture(createSprite(path.c_str()))
	{
		int w, h;
		getSpriteSize(mTexture, w, h);
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

	void Texture::DrawAt(X x, Y y) const noexcept
	{
		drawSprite(mTexture, x, y);
	}

	const Size& Texture::GetSize() const noexcept
	{
		return mSpriteSize;
	}
}
