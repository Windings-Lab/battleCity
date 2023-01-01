#pragma once

#include "SpriteAliases.h"

namespace BattleCity::Sprite
{
	class SpriteData final
	{
	private:
		using TexturePathContainer = std::unordered_map<TextureType, TexturePath>;
		using SpriteFolderAtlas = std::unordered_map<SpritePath, TexturePathContainer>;

	private:
		friend void swap(SpriteData& first, SpriteData& second) noexcept;

	public:
		SpriteData() = default;

		DISALLOW_COPY(SpriteData)
		ALLOW_MOVE(SpriteData)

		~SpriteData() = default;

		void Init(const SpritePath&);
		const TexturePath& Get(TextureType) const;

		TexturePathContainer::const_iterator begin() const;
		TexturePathContainer::const_iterator end() const;

	private:
		std::optional<TextureType> TypeFrom(const std::filesystem::path&) const;


	private:
		static SpriteFolderAtlas mSpritePathAtlas;
		TexturePathContainer mSpritePathContainer;

	};
}
