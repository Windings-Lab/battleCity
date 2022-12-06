#pragma once

#include "Manager.h"

#include <SpriteManager.h>
#include <string>
#include <unordered_map>

namespace BattleCity::Manager
{
	using SpritePathList = std::unordered_map<SpriteManager::SpriteType, std::unordered_map<SpriteManager::SpriteBehaviour, std::string>>;

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

		SpritePathList mSpritePathList;
	};

	inline SpritePathManager& PM = SpritePathManager::GetInstance();
}
