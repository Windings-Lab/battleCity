#pragma once

#include "BCSprite.h"
#include "SpriteAliases.h"
#include "TexturePathContainer.h"

namespace BattleCity::Sprite
{
	class Texture;

	using TextureContainer = std::unordered_map<TextureType, Texture>;

	class SpriteBuilder final
	{
	public:
		SpriteBuilder() = default;

		DISALLOW_COPY_MOVE(SpriteBuilder)

		~SpriteBuilder() = default;

		void BuildPathGroupAt(const SpritePath&);
		void BuildTextures();
		void BuildSpriteWith(TextureType);

		BCSprite GetSprite();

	private:
		BCSprite mSprite;

		TexturePathContainer mTexturePathContainer;
		TextureContainer mTextures;
	};
}
