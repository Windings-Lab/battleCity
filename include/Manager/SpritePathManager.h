#pragma once

#include "PCHeader.h"

#include "Manager.h"
#include "SpriteManager.h"

namespace BattleCity::Manager
{
	using SpriteBehaviourList = std::unordered_map<Object::Behaviour, std::filesystem::path>;
	using SpritePathList = std::unordered_map<SpriteManager::SpriteType, SpriteBehaviourList>;

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

		const std::filesystem::path* GetSpritePath(SpriteManager::SpriteType spriteType, Object::Behaviour objectBehaviour) const;
	private:
		SpritePathManager();

		const std::filesystem::path Path;
		const std::filesystem::path FileExtension;
		SpritePathList mSpritePathList;
	};

	inline SpritePathManager& PM = SpritePathManager::GetInstance();
}
