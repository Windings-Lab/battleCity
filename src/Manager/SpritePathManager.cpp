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
		SpriteFolderPath(".\\data"), FileExtension(".png"),
		mSpritePathList(0)
	{
		
	}

	void SpritePathManager::StartUp()
	{
		try
		{
			for (const auto& entry : std::filesystem::recursive_directory_iterator(SpriteFolderPath))
			{
				if (entry.path().extension() == FileExtension)
				{
					std::string spriteTypeStr = entry.path().stem().string();
					std::string objectBehaviourStr = entry.path().parent_path().stem().string();

					auto spriteTypeCast
						= magic_enum::enum_cast<SpriteType>(spriteTypeStr);
					auto objectBehaviourCast
						= magic_enum::enum_cast<Object::Behaviour>(objectBehaviourStr);

					if (spriteTypeCast.has_value() && objectBehaviourCast.has_value())
					{
						SetSpritePath(entry.path().string(), spriteTypeCast.value(), objectBehaviourCast.value());
					}
					else
					{
						std::cerr << spriteTypeStr << " - " << objectBehaviourStr << ": has not been found\n"
							<< "in folder: " << SpriteFolderPath.string() << std::endl;
					}
				}
			}
		}
		catch (...)
		{
			std::cerr << "Sprite Folder Path has not been found" << std::endl;
			std::cerr << "Make sure that .\\data in folder with BattleCity.exe file" << std::endl;
			std::exit(1);
		}
#ifdef _DEBUG
		OutputAllPath();
		std::cout << "Sprite SpriteFolderPath Manager loaded." << std::endl;
#endif
	}

	void SpritePathManager::ShutDown()
	{
		mSpritePathList.clear();
	}

	std::string SpritePathManager::GetSpritePath(SpriteType spriteType, Object::Behaviour objectBehaviour) const
	{
		try
		{
			return mSpritePathList.at({ spriteType, objectBehaviour });
		}
		catch (std::out_of_range&)
		{
			std::cerr << __FUNCTION__ << ": No sprite with \nSpriteType: "
				<< magic_enum::enum_name(spriteType)
				<< "\nBehaviour: " << magic_enum::enum_name(objectBehaviour)
				<< std::endl;
			return "";
		}
		catch (...)
		{
			std::cerr << __FUNCTION__ << ": Unexpected error" << std::endl;
			return "";
		}
	}
	void SpritePathManager::SetSpritePath(std::string path, SpriteType spriteType, Object::Behaviour objectBehaviour)
	{
		mSpritePathList.try_emplace({ spriteType, objectBehaviour }, path);
	}

	void SpritePathManager::OutputAllPath()
	{
		for (auto& [pair, path] : mSpritePathList)
		{
			std::cout << magic_enum::enum_name(pair.first) << " - "
				<< magic_enum::enum_name(pair.second) << ": " << path << std::endl;
		}
		std::cout << std::endl;
	}
}
