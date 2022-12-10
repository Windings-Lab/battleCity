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

	void SpritePathManager::SetSpritePath(const std::filesystem::path& folderPath)
	{
		using magic_enum::enum_cast;

		const std::string spriteTypeStr = folderPath.stem().string();
		const std::string objectBehaviourStr = folderPath.parent_path().stem().string();

		auto spriteTypeCast = enum_cast<SpriteType>(spriteTypeStr);
		auto objectBehaviourCast = enum_cast<Object::Behaviour>(objectBehaviourStr);

		if (!spriteTypeCast.has_value() || !objectBehaviourCast.has_value())
		{
			std::cerr << spriteTypeStr << " - " << objectBehaviourStr << ": have no usage." << std::endl;
			return;
		}

		SpriteTypeBehaviourPair pair = { spriteTypeCast.value(),objectBehaviourCast.value() };
		mSpritePathList.try_emplace(std::move(pair), folderPath.string());
	}

	void SpritePathManager::StartUp()
	{
		using namespace std::filesystem;

		if(!exists(SpriteFolderPath))
		{
			std::cerr << "Sprite Folder Path has not been found" << std::endl;
			std::cerr << "Make sure that .\\data in folder with BattleCity.exe file" << std::endl;
			std::exit(1);
		}

		for (const auto& folderEntry : recursive_directory_iterator(SpriteFolderPath))
		{
			if (folderEntry.path().extension() != FileExtension)
			{
				continue;
			}

			SetSpritePath(folderEntry.path());
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
		const SpriteTypeBehaviourPair pair = { spriteType, objectBehaviour };

		if(mSpritePathList.find(pair) != mSpritePathList.end())
		{
			return mSpritePathList.at(pair);
		}

		using magic_enum::enum_name;
		std::cerr << __FUNCTION__ << ": No sprite with\n"
			<< "SpriteType: "  << enum_name(spriteType)
			<< "\nBehaviour: " << enum_name(objectBehaviour)
			<< std::endl;

		return "";
	}

	void SpritePathManager::OutputAllPath()
	{
		using magic_enum::enum_name;
		using std::cout;
		using std::endl;

		for (auto& [pair, path] : mSpritePathList)
		{
			cout << enum_name(pair.first) << " - "
				 << enum_name(pair.second)
			     << ": " << path << endl;
		}
		cout << endl;
	}
}
