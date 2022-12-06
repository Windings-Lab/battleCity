#include "PCHeader.h"
#include "SpritePathManager.h"

namespace BattleCity::Manager
{
	SpritePathManager& SpritePathManager::GetInstance()
	{
		static SpritePathManager pathManager;
		return pathManager;
	}

	SpritePathManager::SpritePathManager() : Manager(Type::SpritePath),
		Path(".\\data"), FileExtension(".png"),
		mSpritePathList(0)
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
						SetSpritePath(entry.path().string(), objectTypeCast.value(), spriteBehaviourCast.value());
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

	std::string SpritePathManager::GetSpritePath(SpriteManager::SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		try
		{
			return mSpritePathList.at(spriteType).at(objectBehaviour).string();
		}
		catch (std::out_of_range& ex)
		{
			std::cerr << ex.what() << std::endl;
			return "";
		}
	}
	void SpritePathManager::SetSpritePath(std::string path, SpriteManager::SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		if (mSpritePathList.count(spriteType) == 0)
		{
			SpriteObjectBehaviourPath behaviourMap;
			behaviourMap.try_emplace(objectBehaviour, path);
			mSpritePathList.try_emplace(spriteType, std::move(behaviourMap));
		}
		else
		{
			try
			{
				mSpritePathList.at(spriteType).try_emplace(objectBehaviour, path);
			}
			catch (std::out_of_range& ex)
			{
				std::cerr << ex.what() << std::endl;
			}
		}
	}
}
