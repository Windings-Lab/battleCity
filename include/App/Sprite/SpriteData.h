#pragma once

namespace BattleCity::Sprite
{
	class SpriteData final
	{
	private:
		using SpritePath = std::string;
		using FolderPath = std::string;

		using SpritePathContainer = std::unordered_map<Type, SpritePath>;
		using SpritePathAtlas = std::unordered_map<FolderPath, SpritePathContainer>;

	public:
		SpriteData() = default;

		DISALLOW_COPY(SpriteData)
		ALLOW_MOVE(SpriteData)

		~SpriteData() = default;

		void Init(const FolderPath& folderPath);
		const SpritePath& Get(Type spriteType) const;

		SpritePathContainer::const_iterator begin() const;
		SpritePathContainer::const_iterator end() const;

	private:
		std::optional<Type> TypeFrom(const std::filesystem::path& spritePath) const;
		friend void swap(SpriteData& first, SpriteData& second) noexcept;

	private:
		static SpritePathAtlas mSpritePathAtlas;
		SpritePathContainer mSpritePathContainer;

	};
}
