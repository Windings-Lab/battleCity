#include "PCHeader.h"
#include "SpriteData.h"

namespace BattleCity::Sprite
{
	void SpriteData::Init(const std::string& folderPath)
	{
		using namespace std::filesystem;

		const path pathFS(folderPath);

		if (!exists(pathFS))
		{
			std::cerr << "Sprite Folder Path has not been found\n";
			std::cerr << "Make sure that " << folderPath << " in folder with BattleCity.exe file\n";
			throw std::invalid_argument("Can't find sprite folder");
		}

		const path fileExtension = ".png";
		for (const auto& folderEntry : recursive_directory_iterator(pathFS))
		{
			if (folderEntry.path().extension() != fileExtension)
			{
				continue;
			}

			const auto& type= TypeFrom(folderEntry.path());
			if (!type.has_value())
			{
				continue;
			}

			mSpritePathContainer.emplace(type.value(), folderEntry.path().string());
		}
	}

	const std::string& SpriteData::Get(Type spritePair) const
	{
		const auto& spritePathIterator = mSpritePathContainer.find(spritePair);
		if (spritePathIterator == mSpritePathContainer.end())
		{
			throw std::out_of_range("Sprite data has not been created");
		}

		return spritePathIterator->second;
	}

	std::unordered_map<Type, std::string>::const_iterator SpriteData::begin() const
	{
		return mSpritePathContainer.cbegin();
	}

	std::unordered_map<Type, std::string>::const_iterator SpriteData::end() const
	{
		return mSpritePathContainer.cend();
	}

	std::optional<Type> SpriteData::TypeFrom(const std::filesystem::path& spritePath) const
	{
		using magic_enum::enum_cast;

		const std::string spriteTypeStr = spritePath.stem().string();
		const auto& spriteTypeCast= enum_cast<Type>(spriteTypeStr);

		if (!spriteTypeCast.has_value())
		{
			std::cerr << spriteTypeStr << ": have no usage.\n";
		}

		return spriteTypeCast;
	}
}
