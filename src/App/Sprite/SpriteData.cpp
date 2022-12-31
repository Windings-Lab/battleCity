#include "PCHeader.h"
#include "SpriteData.h"

namespace BattleCity::Sprite
{
	SpriteData::SpritePathAtlas SpriteData::mSpritePathAtlas;

	SpriteData::SpriteData(SpriteData&& mve) noexcept : SpriteData()
	{
		swap(*this, mve);
	}

	SpriteData& SpriteData::operator=(SpriteData&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	void SpriteData::Init(const FolderPath& folderPath)
	{
		using namespace std::filesystem;

		if  (
			const auto& pathContainerIt = mSpritePathAtlas.find(folderPath); 
			pathContainerIt != mSpritePathAtlas.end()
			)
		{
			mSpritePathContainer = pathContainerIt->second;
			return;
		}

		const path folderPathFs(folderPath);
		if (!exists(folderPathFs))
		{
			std::cerr << "Sprite Folder Path has not been found\n";
			std::cerr << "Make sure that " << folderPath << " in folder with BattleCity.exe file\n";
			throw std::invalid_argument("Can't find sprite folder");
		}

		const path fileExtension = ".png";
		for (const auto& folderEntry : recursive_directory_iterator(folderPathFs))
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

			mSpritePathContainer.try_emplace(type.value(), folderEntry.path().string());
		}

		mSpritePathAtlas.try_emplace(folderPath, mSpritePathContainer);
	}
	const SpriteData::SpritePath& SpriteData::Get(TextureType spriteType) const
	{
		const auto& spritePathIterator = mSpritePathContainer.find(spriteType);
		if (spritePathIterator == mSpritePathContainer.end())
		{
			throw std::out_of_range("Sprite data has not been created");
		}

		return spritePathIterator->second;
	}

	std::optional<TextureType> SpriteData::TypeFrom(const std::filesystem::path& spritePath) const
	{
		using magic_enum::enum_cast;

		const std::string spriteTypeStr = spritePath.stem().string();
		const auto& spriteTypeCast= enum_cast<TextureType>(spriteTypeStr);

		if (!spriteTypeCast.has_value())
		{
			std::cerr << spriteTypeStr << ": have no usage.\n";
		}

		return spriteTypeCast;
	}

	SpriteData::SpritePathContainer::const_iterator SpriteData::begin() const
	{
		return mSpritePathContainer.cbegin();
	}
	SpriteData::SpritePathContainer::const_iterator SpriteData::end() const
	{
		return mSpritePathContainer.cend();
	}

	void swap(SpriteData& first, SpriteData& second) noexcept
	{
		first.mSpritePathContainer.swap(second.mSpritePathContainer);
	}
}
