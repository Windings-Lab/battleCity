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

		swap(f.mName, s.mName);
		swap(f.mType, s.mType);

		swap(f.mWidth, s.mWidth);
		swap(f.mHeight, s.mHeight);
	}

	Texture::Texture(const char* path, const TextureName name, const TextureType type)
		: Texture(createSprite(path), name, type, 0, 0, 0, 0)
	{
		getSpriteSize(mTexture, mWidth, mHeight);
	}

	Texture::Texture()
		: Texture(nullptr, TextureName::Error, TextureType::Error, 0, 0, 0, 0) {}
	Texture::Texture(Sprite* texture, TextureName name, TextureType type, X x , Y y, Width w, Height h)
		: mTexture(texture)
		, mName(name)
		, mType(type)
		, mX(x)
		, mY(y)
		, mWidth(w)
		, mHeight(h)
	{}

	Texture::Texture(Texture&& mve) noexcept : Texture()
	{
		swap(*this, mve);
	}
	Texture& Texture::operator=(Texture&& mve) noexcept
	{
		Texture temp(std::move(mve));
		swap(*this, temp);
		return *this;
	}
	Texture::~Texture()
	{
		if(mTexture)
		{
			destroySprite(mTexture);
		}
	}

	void Texture::DrawAt(X x, Y y, Interpolation interpolation) const noexcept
	{
		mX = mX + static_cast<X>(static_cast<Interpolation>(x - mX) * interpolation);
		mY = mY + static_cast<Y>(static_cast<Interpolation>(y - mY) * interpolation);

		drawSprite(mTexture, x, y);
	}
	void Texture::SetDrawPosition(X x, Y y) const noexcept
	{
		mX = x;
		mY = y;
	}

	TextureName Texture::GetName() const noexcept
	{
		return mName;
	}

	TextureType Texture::GetType() const noexcept
	{
		return mType;
	}

	void Texture::GetSize(Width& w, Height& h) const noexcept
	{
		w = mWidth;
		h = mHeight;
	}
}
