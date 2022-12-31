#include "PCHeader.h"

#include "BCSprite.h"

#include "Texture.h"

namespace BattleCity::Sprite
{
	void swap(BCSprite& first, BCSprite& second) noexcept
	{
		using std::swap;

		swap(first.mCurrentTexture, second.mCurrentTexture);
		swap(first.mTextureType, second.mTextureType);
		first.mSpriteContainer.swap(second.mSpriteContainer);
	}

	BCSprite::BCSprite() : mCurrentTexture(nullptr){}
	BCSprite::BCSprite(SpriteContainer& spriteContainer)
		: mCurrentTexture(nullptr)
		, mSpriteContainer(std::move(spriteContainer))
	{
	}
	BCSprite::BCSprite(BCSprite&& mve) noexcept : BCSprite()
	{
		swap(*this, mve);
	}
	BCSprite& BCSprite::operator=(BCSprite&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	void BCSprite::DrawAt(X x, Y y) const noexcept
	{
		mCurrentTexture->DrawAt(x, y);
	}
	const Vector2Int& BCSprite::GetSpriteSize() const noexcept
	{
		return mCurrentTexture->GetSize();
	}

	void BCSprite::ChangeTexture(TextureType textureType)
	{
		mCurrentTexture = &mSpriteContainer.at(textureType);
	}
}
