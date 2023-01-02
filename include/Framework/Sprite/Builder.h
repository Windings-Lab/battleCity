#pragma once

#include "BCSprite.h"
#include "TexturePath/Group.h"

namespace BattleCity::Sprite
{
	class Builder final
	{
	public:
		Builder() = default;

		DISALLOW_COPY_MOVE(Builder)

		~Builder() = default;

		void BuildPathGroupAt(const FolderPath&);
		void BuildTextures();
		void BuildSpriteWith(Texture::Type);

		BCSprite GetSprite();

	private:
		BCSprite mSprite;

		Texture::Group mTexturePathContainer;
		TextureContainer mTextures;
	};
}
