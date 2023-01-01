#include "PCHeader.h"
#include "ObjectBuilder.h"

namespace BattleCity::Object
{
	void ObjectBuilder::BuildSpriteData(const Sprite::SpritePath& path)
	{
		mSpriteData = std::make_unique<Sprite::SpriteData>();
		mSpriteData->Init(path);
	}
	void ObjectBuilder::BuildTextures()
	{
		if (mSpriteData == nullptr)
		{
			std::cerr << "Build Sprite Data first\n";
			return;
		}
		mTextures.clear();
		for (const auto& [textureType, texturePath] : *mSpriteData)
		{
			Sprite::Texture texture = Sprite::Texture::Create(texturePath);
			mTextures.try_emplace(textureType, std::move(texture));
		}
	}
	void ObjectBuilder::BuildSprite()
	{
		mSprite = std::make_unique<Sprite::BCSprite>(mTextures);
	}
}
