#include "PCHeader.h"
#include "SpriteBuilder.h"

#include "BCSprite.h"
#include "TexturePathContainer.h"
#include "Texture.h"

namespace BattleCity::Sprite
{
	void SpriteBuilder::BuildPathGroupAt(const SpritePath& path)
	{
		mTexturePathContainer.Init(path);
	}
	void SpriteBuilder::BuildTextures()
	{
		if (mTexturePathContainer.IsEmpty())
		{
			std::cerr << "Build Sprite Data first\n";
			return;
		}
		if (!mTextures.empty())
		{
			std::cerr << "Textures has already been built\n";
			return;
		}

		for (const auto& [textureType, texturePath] : mTexturePathContainer)
		{
			mTextures.try_emplace(textureType, Texture(texturePath));
		}
	}
	void SpriteBuilder::BuildSpriteWith(TextureType type)
	{
		mSprite = BCSprite(mTextures);
		mSprite.ChangeTexture(type);
	}

	BCSprite SpriteBuilder::GetSprite()
	{
		mTexturePathContainer.Clear();
		mTextures.clear();

		return std::move(mSprite);
	}
}
