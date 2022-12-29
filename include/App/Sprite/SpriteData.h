#pragma once

namespace BattleCity::Sprite
{
	class SpriteData final
	{
	public:
		SpriteData() = default;

		DISALLOW_COPY(SpriteData)
		ALLOW_MOVE(SpriteData)

		~SpriteData() = default;

		void Init(const std::string& folderPath);
		const std::string& Get(Type spritePair) const;

		std::unordered_map<Type, std::string>::const_iterator begin() const;
		std::unordered_map<Type, std::string>::const_iterator end() const;

	private:
		std::optional<Type> TypeFrom(const std::filesystem::path& spritePath) const;
		friend void swap(SpriteData& first, SpriteData& second) noexcept;

	private:
		using SpritePathContainer = std::unordered_map<Type, std::string>;

		SpritePathContainer mSpritePathContainer;
	};
}
