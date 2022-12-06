#pragma once

#include "Manager.h"
#include "SpriteManager.h"

#include <filesystem>
#include <unordered_map>

namespace BattleCity::Manager
{
	using SpriteBehaviourList = std::unordered_map<Object::Behaviour, std::string>;
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

		const SpritePathList& GetSpritePathList() const;
	private:
		SpritePathManager();

		const std::filesystem::path Path;
		const std::filesystem::path FileExtension;
		SpritePathList mSpritePathList;
	};

	inline SpritePathManager& PM = SpritePathManager::GetInstance();
}
