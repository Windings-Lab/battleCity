#pragma once

namespace BattleCity::Sprite
{
	class SpriteData final
	{
	public:
		SpriteData() = default;

		DISALLOW_COPY_MOVE(SpriteData)

		~SpriteData() = default;

		void Init(const std::filesystem::path& folderPath);
		const std::string& Get(Type spritePair) const;

		std::unordered_map<Type, std::string>::const_iterator begin() const;
		std::unordered_map<Type, std::string>::const_iterator end() const;

	private:
		std::optional<Type> TypeFrom(const std::filesystem::path& spritePath) const;

	private:
		using SpritePathContainer = std::unordered_map<Type, std::string>;

		SpritePathContainer mSpritePathContainer;
	};
}
