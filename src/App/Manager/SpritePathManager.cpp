#include "PCHeader.h"
#include "SpritePathManager.h"

namespace BattleCity::Manager
{
	namespace 
	{
		void OutputAllPath(const SpritePathManager::SpriteData& spritePathList)
		{
			using magic_enum::enum_name;
			using std::cout;
			using std::endl;

			std::vector<Sprite::SpritePair> keys(spritePathList.size());
			transform(spritePathList.begin(), spritePathList.end(), keys.begin(), [](auto& pair) { return pair.first; });
			std::sort(keys.begin(), keys.end());

			for (auto& pair : keys)
			{
				cout << enum_name(pair.first) << " - "
					<< enum_name(pair.second)
					<< ": " << spritePathList.at(pair) << endl;
			}
			cout << endl;
		}
	}

	SpritePathManager& SpritePathManager::GetInstance()
	{
		static SpritePathManager pathManager;
		return pathManager;
	}

	SpritePathManager::SpritePathManager() : Manager() {}

	void SpritePathManager::StartUp()
	{
		__super::StartUp();

		CreateSpriteDataAt(".\\data");

#ifdef _DEBUG
		OutputAllPath(mSpriteData);
#endif
	}

	void SpritePathManager::ShutDown()
	{
		mSpriteData.clear();
	}

	const std::string& SpritePathManager::GetSpritePath(const Sprite::SpritePair& spritePair) const
	{
		const auto& spritePathIterator = mSpriteData.find(spritePair);
		if (spritePathIterator == mSpriteData.end())
		{
			throw std::out_of_range("Sprite data has not been created");
		}

		return spritePathIterator->second;
	}

	std::optional<Sprite::SpritePair> SpritePathManager::CreateSpritePairFrom
		(const std::filesystem::path& spritePath)
	{
		using magic_enum::enum_cast;

		const std::string spriteTypeStr = spritePath.stem().string();
		const std::string objectBehaviourStr = spritePath.parent_path().stem().string();

		auto spriteTypeCast
			= enum_cast<Sprite::Type>(spriteTypeStr);
		auto objectBehaviourCast
			= enum_cast<Sprite::Behaviour>(objectBehaviourStr);

		if (!spriteTypeCast.has_value() || !objectBehaviourCast.has_value())
		{
			std::cerr << spriteTypeStr << " - " << objectBehaviourStr << ": have no usage.\n";
			return {};
		}

		return std::make_pair(spriteTypeCast.value(), objectBehaviourCast.value());
	}

	void SpritePathManager::CreateSpriteDataAt(const std::filesystem::path& folderPath)
	{
		using namespace std::filesystem;

		if (!exists(folderPath))
		{
			std::cerr << "Sprite Folder Path has not been found\n";
			std::cerr << "Make sure that " << folderPath << " in folder with BattleCity.exe file\n";
			throw std::invalid_argument("Can't find data folder");
		}

		const path fileExtension = ".png";
		for (const auto& folderEntry : recursive_directory_iterator(folderPath))
		{
			if (folderEntry.path().extension() != fileExtension)
			{
				continue;
			}

			const auto& pair
				= CreateSpritePairFrom(folderEntry.path());
			if(!pair.has_value())
			{
				continue;
			}

			mSpriteData.emplace(pair.value(), folderEntry.path().string());
		}
	}
}
