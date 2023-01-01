#include "PCHeader.h"
#include "SpriteData.h"

namespace BattleCity::Sprite
{
	SpriteData::SpriteFolderAtlas SpriteData::mSpritePathAtlas;

	SpriteData::SpriteData(SpriteData&& mve) noexcept : SpriteData()
	{
		swap(*this, mve);
	}

	SpriteData& SpriteData::operator=(SpriteData&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	void SpriteData::Init(const SpritePath& spritePath)
	{
		using namespace std::filesystem;

		if  (
			const auto& pathContainerIt = mSpritePathAtlas.find(spritePath); 
			pathContainerIt != mSpritePathAtlas.end()
			)
		{
			mSpritePathContainer = pathContainerIt->second;
			return;
		}

		const path spritePathFS(spritePath);
		if (!exists(spritePathFS))
		{
			std::cerr << "Sprite Folder Path has not been found\n";
			std::cerr << "Make sure that " << spritePath << " in folder with BattleCity.exe file\n";
			throw std::invalid_argument("Can't find sprite folder");
		}

		const path fileExtension = ".png";
		for (const auto& folderEntry : recursive_directory_iterator(spritePathFS))
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

		mSpritePathAtlas.try_emplace(spritePath, mSpritePathContainer);
	}
	const TexturePath& SpriteData::Get(TextureType spriteType) const
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

	SpriteData::TexturePathContainer::const_iterator SpriteData::begin() const
	{
		return mSpritePathContainer.cbegin();
	}
	SpriteData::TexturePathContainer::const_iterator SpriteData::end() const
	{
		return mSpritePathContainer.cend();
	}

	void swap(SpriteData& first, SpriteData& second) noexcept
	{
		first.mSpritePathContainer.swap(second.mSpritePathContainer);
	}
}
