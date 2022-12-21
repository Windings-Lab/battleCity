#pragma once

#include "Manager.h"

namespace BattleCity::Manager
{
	class SpritePathManager final : public Manager
	{
		using SpritePathList = std::unordered_map<SpriteBehaviour, std::string>;
	public:
		static SpritePathManager& GetInstance();

		SpritePathManager(const SpritePathManager&) = delete;
		SpritePathManager(SpritePathManager&&) = delete;

		SpritePathManager& operator=(const SpritePathManager&) = delete;
		SpritePathManager& operator=(SpritePathManager&&) = delete;

		~SpritePathManager() override = default;

	public:
		void StartUp() override;
		void ShutDown() override;

		std::optional<std::string> GetSpritePath(SpriteType spriteType, Object::Behaviour objectBehaviour) const;
	private:
		void SetSpritePath(const std::filesystem::path& folderPath);
		void OutputAllPath();
	private:
		SpritePathManager();

		const std::filesystem::path SpriteFolderPath;
		const std::filesystem::path FileExtension;
		SpritePathList mSpritePathList;
	};

	constexpr auto& PM = SpritePathManager::GetInstance;
}
