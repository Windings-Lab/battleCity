#pragma once

#include "SpriteAliases.h"

#include "BCSprite.h"
#include "SpriteData.h"

namespace BattleCity::Object
{
	class ObjectBuilder
	{
	public:
		ObjectBuilder() = default;

		DISALLOW_COPY_MOVE(ObjectBuilder)

		virtual ~ObjectBuilder() = default;

		virtual void BuildSpriteData(const Sprite::SpritePath& path);
		virtual void BuildTextures();
		virtual void BuildSprite();

	private:
		std::unique_ptr<Sprite::SpriteData> mSpriteData;
		Sprite::TextureContainer mTextures;
		std::unique_ptr<Sprite::BCSprite> mSprite;
	};
}
