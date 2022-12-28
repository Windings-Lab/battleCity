#pragma once

#include "Manager.h"

namespace BattleCity::Manager
{
	class SpritePathManager final : public Manager
	{
	public:
		static SpritePathManager& GetInstance();

	private:
		SpritePathManager();

	public:
		DISALLOW_COPY_MOVE(SpritePathManager)

		~SpritePathManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		const std::string& GetSpritePath(const Sprite::SpritePair& spritePair) const;
		void CreateSpriteDataAt(const std::filesystem::path& folderPath);

	private:
		std::optional<Sprite::SpritePair> CreateSpritePairFrom(const std::filesystem::path& spritePath);

	public:
		using SpriteData = std::unordered_map<Sprite::SpritePair, std::string, Sprite::SpritePairHash>;

	private:
		SpriteData mSpriteData;

	};

	constexpr auto& PM = SpritePathManager::GetInstance;
}
