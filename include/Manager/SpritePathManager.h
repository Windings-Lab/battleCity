#pragma once

#include "Manager.h"

namespace BattleCity::Manager
{
	using SpritePathList = std::unordered_map<SpriteTypeBehaviourPair, std::string>;

	class SpritePathManager final : public Manager
	{
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

		std::string GetSpritePath(SpriteType spriteType, Object::Behaviour objectBehaviour) const;
	private:
		void SetSpritePath(std::string path, SpriteType spriteType, Object::Behaviour objectBehaviour);
		void OutputAllPath();
	private:
		SpritePathManager();

		const std::filesystem::path SpriteFolderPath;
		const std::filesystem::path FileExtension;
		SpritePathList mSpritePathList;
	};

	inline SpritePathManager& PM = SpritePathManager::GetInstance();
}
