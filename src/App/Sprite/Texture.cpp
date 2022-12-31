#include "PCHeader.h"
#include "Texture.h"

namespace BattleCity::Sprite
{
	namespace
	{
		FRAMEWORK_API Sprite* createSprite(TexturePath path);
		FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
		FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int& h);
		FRAMEWORK_API void destroySprite(Sprite* s);
	}

	Texture::Texture(Sprite& texture, const TextureSize& size)
		: mTexture(&texture), mSpriteSize(size.X, size.Y)
	{

	}

	Texture::~Texture()
	{
		destroySprite(mTexture);
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
