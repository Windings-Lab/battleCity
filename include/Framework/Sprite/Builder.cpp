#include "PCHeader.h"
#include "Builder.h"

#include "BCSprite.h"

namespace BattleCity::Sprite
{
	void Builder::BuildPathGroupAt(const FolderPath& path)
	{
		mTexturePathContainer.Init(path);
	}
	void Builder::BuildTextures()
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
			mTextures.try_emplace(textureType, Texture::Texture(texturePath));
		}
	}
	void Builder::BuildSpriteWith(Texture::Type type)
	{
		mSprite = BCSprite(mTextures);
		mSprite.ChangeTexture(type);
	}

	BCSprite Builder::GetSprite()
	{
		mTexturePathContainer.Clear();
		mTextures.clear();

		return std::move(mSprite);
	}
}
