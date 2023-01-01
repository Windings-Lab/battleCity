#include "PCHeader.h"
#include "Texture.h"

namespace BattleCity::Sprite
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
	}

	Texture::Texture() : mTexture(nullptr) {}

	Texture::Texture(Sprite& texture, const TextureSize& size)
		: mTexture(&texture), mSpriteSize(size.X, size.Y)
	{

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

	Texture Texture::Create(const TexturePath& path)
	{
		Sprite& sprite = *createSprite(path.c_str());
		int w, h;
		getSpriteSize(&sprite, w, h);

		return { sprite, TextureSize(w, h) };
	}

	void Texture::DrawAt(X x, Y y) const noexcept
	{
		drawSprite(mTexture, x, y);
	}

	const TextureSize& Texture::GetSize() const noexcept
	{
		return mSpriteSize;
	}
}
