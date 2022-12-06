#include "SpritePathManager.h"

#include <filesystem>
#include <iostream>

namespace BattleCity::Manager
{
	SpritePathManager& SpritePathManager::GetInstance()
	{
		static SpritePathManager pathManager;
		return pathManager;
	}

	SpritePathManager::SpritePathManager() : Manager(Manager::Type::SpritePath)
	{
		
	}


	void SpritePathManager::StartUp()
	{
		std::filesystem::path pngPath(".\\data");
		std::filesystem::path ext(".png");
		for (const auto& entry : std::filesystem::recursive_directory_iterator(pngPath))
		{
			if (entry.path().extension() == ext)
				std::cout << entry.path().parent_path().stem() << std::endl;
		}
	}

	void SpritePathManager::ShutDown()
	{
	}

	const SpritePathList& SpritePathManager::GetSpritePathList() const
	{
		return mSpritePathList;
	}
}
