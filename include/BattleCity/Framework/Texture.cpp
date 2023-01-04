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

	Texture::Texture()
		: mTexture(nullptr)
		, mName(TextureName::Error)
		, mType(TextureType::Error)
		, mWidth(0)
		, mHeight(0)
	{}
	Texture::Texture(const std::filesystem::path& path)
		: mTexture(createSprite(path.string().c_str()))
		, mName(magic_enum::enum_cast<TextureName>(path.parent_path().stem().string()).value_or(TextureName::Error))
		, mType(magic_enum::enum_cast<TextureType>(path.stem().string()).value_or(TextureType::Error))
	{
		if (mTexture)
		{
			getSpriteSize(mTexture, mWidth, mHeight);
		}
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

	TextureName Texture::GetName() const noexcept
	{
		return mName;
	}

	TextureType Texture::GetType() const noexcept
	{
		return mType;
	}

	void Texture::GetSize(int& w, int& h) const noexcept
	{
		w = mWidth;
		h = mHeight;
	}
}
