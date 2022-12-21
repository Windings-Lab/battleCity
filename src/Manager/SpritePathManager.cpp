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
			std::cerr << spriteTypeStr << " - " << objectBehaviourStr << ": have no usage.\n";
			return;
		}

		SpriteBehaviour pair = { spriteTypeCast.value(),objectBehaviourCast.value() };
		mSpritePathList.try_emplace(std::move(pair), folderPath.string());
	}

	void SpritePathManager::StartUp()
	{
		__super::StartUp();

		using namespace std::filesystem;

		if(!exists(SpriteFolderPath))
		{
			std::cerr << "Sprite Folder Path has not been found\n";
			std::cerr << "Make sure that .\\data in folder with BattleCity.exe file\n";
			throw std::invalid_argument("Can't find data folder");
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
#endif
	}

	void SpritePathManager::ShutDown()
	{
		mSpritePathList.clear();
	}

	std::optional<std::string> SpritePathManager::GetSpritePath(const SpriteBehaviour& spriteBehaviour) const
	{
		return
				mSpritePathList.find(spriteBehaviour) != mSpritePathList.end()
				? std::optional(mSpritePathList.at(spriteBehaviour))
				: std::optional<std::string>();
	}

	void SpritePathManager::OutputAllPath()
	{
		using magic_enum::enum_name;
		using std::cout;
		using std::endl;

		std::vector<SpriteBehaviour> keys(mSpritePathList.size());
		transform(mSpritePathList.begin(), mSpritePathList.end(), keys.begin(), [](auto& pair) { return pair.first; });
		std::sort(keys.begin(), keys.end());

		for (auto& pair : keys)
		{
			cout << enum_name(pair.first) << " - "
				 << enum_name(pair.second)
			     << ": " << mSpritePathList.at(pair) << endl;
		}
		cout << endl;
	}
}
