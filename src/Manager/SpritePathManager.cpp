#include "SpritePathManager.h"

#include <iostream>
#include <magic_enum.hpp>
#include <string>

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
				std::string objectTypeStr = entry.path().stem().string();
				auto objectTypeCast
					= magic_enum::enum_cast<SpriteManager::SpriteType>(objectTypeStr);

				if(objectTypeCast.has_value())
				{
					std::string spriteBehaviourStr = entry.path().parent_path().stem().string();
					auto spriteBehaviourCast
						= magic_enum::enum_cast<Object::Behaviour>(spriteBehaviourStr);
					if(spriteBehaviourCast.has_value())
					{
						if(mSpritePathList.count(objectTypeCast.value()) == 0)
						{
							SpriteBehaviourList behaviourMap;
							behaviourMap.try_emplace(spriteBehaviourCast.value(), entry.path().string());
							mSpritePathList.try_emplace(objectTypeCast.value(), behaviourMap);
						}
						else
						{
							mSpritePathList.at(objectTypeCast.value())
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
					std::cerr << "No object type value: " << objectTypeStr << std::endl;
				}
			}
		}
	}

	void SpritePathManager::ShutDown()
	{
	}

	const std::filesystem::path* SpritePathManager::GetSpritePath(SpriteManager::SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		try
		{
			return &mSpritePathList.at(spriteType).at(objectBehaviour);
		}
		catch (std::out_of_range& ex)
		{
			std::cerr << ex.what() << std::endl;
			return nullptr;
		}
	}
}
