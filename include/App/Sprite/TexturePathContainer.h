#pragma once

#include "SpriteAliases.h"

namespace BattleCity::Sprite
{
	class TexturePathContainer final
	{
	private:
		using Container = std::unordered_map<TextureType, TexturePath>;
		using SpritePathAtlas = std::unordered_map<SpritePath, Container>;

	private:
		friend void swap(TexturePathContainer& first, TexturePathContainer& second) noexcept;

	public:
		TexturePathContainer() = default;

		DISALLOW_COPY(TexturePathContainer)
		ALLOW_MOVE(TexturePathContainer)

		~TexturePathContainer() = default;

		void Init(const SpritePath&);
		const TexturePath& Get(TextureType) const;

		Container::const_iterator begin() const;
		Container::const_iterator end() const;

		bool IsEmpty() const;
		void Clear();

	private:
		std::optional<TextureType> TypeFrom(const std::filesystem::path&) const;


	private:
		static SpritePathAtlas mSpritePathAtlas;
		Container mSpritePathContainer;

	};
}
