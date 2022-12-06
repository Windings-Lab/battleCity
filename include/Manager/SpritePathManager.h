#pragma once

#include "Manager.h"

#include <string>
#include <vector>

namespace BattleCity::Manager
{
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
	private:
		SpritePathManager();

		std::vector<std::string> mSpritePathList;
	};

	inline SpritePathManager& PM = SpritePathManager::GetInstance();
}
