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
		SpritePathManager(const SpritePathManager&) = delete;
		SpritePathManager(SpritePathManager&&) = delete;

		SpritePathManager& operator=(const SpritePathManager&) = delete;
		SpritePathManager& operator=(SpritePathManager&&) = delete;

		~SpritePathManager() override = default;

		void StartUp() override;
		void ShutDown() override;

		const std::string& GetSpritePath(const Sprite::SpritePair& spritePair) const;

		void CreateSpriteDataAt(const std::filesystem::path& folderPath);

	public:
		using SpriteData = std::unordered_map<Sprite::SpritePair, std::string, Sprite::SpritePairHash>;

	private:

		SpriteData mSpriteData;
	};

	constexpr auto& PM = SpritePathManager::GetInstance;
}
