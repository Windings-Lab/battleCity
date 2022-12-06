#include "SpritePathManager.h"

#include <filesystem>
#include <iostream>

#include <magic_enum.hpp>

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
			{
				std::string spriteTypeStr = entry.path().stem().string();
				auto spriteTypeCast
					= magic_enum::enum_cast<SpriteManager::SpriteType>(spriteTypeStr);

				if(spriteTypeCast.has_value())
				{
					std::string spriteBehaviourStr = entry.path().parent_path().stem().string();
					auto spriteBehaviourCast
						= magic_enum::enum_cast<SpriteManager::SpriteBehaviour>(spriteBehaviourStr);
					if(spriteBehaviourCast.has_value())
					{
						if(mSpritePathList.count(spriteTypeCast.value()) == 0)
						{
							SpriteBehaviourList testBehaviourList;
							testBehaviourList.try_emplace(spriteBehaviourCast.value(), entry.path().string());
							mSpritePathList.try_emplace(spriteTypeCast.value(), testBehaviourList);
						}
						else
						{
							mSpritePathList.at(spriteTypeCast.value())
								.try_emplace(spriteBehaviourCast.value(), entry.path().string());
						}
					}
				}
			}
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
