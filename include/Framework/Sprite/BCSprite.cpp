#include "PCHeader.h"
#include "BCSprite.h"

namespace BattleCity::Sprite
{
	void swap(BCSprite& first, BCSprite& second) noexcept
	{
		first.mCurrentTexture = second.mCurrentTexture;
		first.mSpriteContainer.swap(second.mSpriteContainer);
	}

	BCSprite::BCSprite() : mCurrentTexture(nullptr) {}
	BCSprite::BCSprite(TextureContainer& spriteContainer)
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

	BCSprite::~BCSprite() = default;

	void BCSprite::DrawAt(X x, Y y) const noexcept
	{
		mCurrentTexture->DrawAt(x, y);
	}
	const BattleCity::Texture::Size& BCSprite::GetSize() const noexcept
	{
		return mCurrentTexture->GetSize();
	}

	void BCSprite::ChangeTexture(BattleCity::Texture::Type textureType)
	{
		mCurrentTexture = &mSpriteContainer.at(textureType);
	}
}
