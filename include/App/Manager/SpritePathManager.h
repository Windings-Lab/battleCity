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

	public:
		void StartUp() override;
		void ShutDown() override;

		std::optional<std::string> GetSpritePath(const SpriteBehaviour& spriteBehaviour) const;

	private:
		void SetSpritePath(const std::filesystem::path& folderPath);
		void OutputAllPath();

	private:
		using SpritePathList = std::unordered_map<SpriteBehaviour, std::string>;

		const std::filesystem::path SpriteFolderPath;
		const std::filesystem::path FileExtension;
		SpritePathList mSpritePathList;
	};

	constexpr auto& PM = SpritePathManager::GetInstance;
}
