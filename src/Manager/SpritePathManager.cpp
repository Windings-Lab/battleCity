#include "SpritePathManager.h"

#include <iostream>
#include <magic_enum.hpp>

namespace BattleCity::Manager
{
	SpritePathManager& SpritePathManager::GetInstance()
	{
		static SpritePathManager pathManager;
		return pathManager;
	}

	SpritePathManager::SpritePathManager() : Manager(Type::SpritePath),
		Path(".\\data"), FileExtension(".png")
	{
		
	}

	void SpritePathManager::StartUp()
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(Path))
		{
			if (entry.path().extension() == FileExtension)
			{
				std::string spriteTypeStr = entry.path().stem().string();
				auto spriteTypeCast
					= magic_enum::enum_cast<SpriteManager::SpriteType>(spriteTypeStr);

				if(spriteTypeCast.has_value())
				{
					std::string spriteBehaviourStr = entry.path().parent_path().stem().string();
					auto spriteBehaviourCast
						= magic_enum::enum_cast<Object::Behaviour>(spriteBehaviourStr);
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
					else
					{
						std::cerr << "No sprite behaviour value: " << spriteBehaviourStr << std::endl;
					}
				}
				else
				{
					std::cerr << "No object type value: " << spriteTypeStr << std::endl;
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
