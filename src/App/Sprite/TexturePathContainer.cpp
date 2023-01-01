#include "PCHeader.h"

#include "TexturePathContainer.h"

namespace BattleCity::Sprite
{
	TexturePathContainer::SpritePathAtlas TexturePathContainer::mSpritePathAtlas;

	TexturePathContainer::TexturePathContainer(TexturePathContainer&& mve) noexcept : TexturePathContainer()
	{
		swap(*this, mve);
	}

	TexturePathContainer& TexturePathContainer::operator=(TexturePathContainer&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	void TexturePathContainer::Init(const SpritePath& spritePath)
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
	const TexturePath& TexturePathContainer::Get(TextureType spriteType) const
	{
		const auto& spritePathIterator = mSpritePathContainer.find(spriteType);
		if (spritePathIterator == mSpritePathContainer.end())
		{
			throw std::out_of_range("Sprite data has not been created");
		}

		return spritePathIterator->second;
	}

	std::optional<TextureType> TexturePathContainer::TypeFrom(const std::filesystem::path& spritePath) const
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

	TexturePathContainer::Container::const_iterator TexturePathContainer::begin() const
	{
		return mSpritePathContainer.cbegin();
	}
	TexturePathContainer::Container::const_iterator TexturePathContainer::end() const
	{
		return mSpritePathContainer.cend();
	}

	bool TexturePathContainer::IsEmpty() const
	{
		return mSpritePathContainer.empty();
	}

	void TexturePathContainer::Clear()
	{
		mSpritePathContainer.clear();
	}

	void swap(TexturePathContainer& first, TexturePathContainer& second) noexcept
	{
		first.mSpritePathContainer.swap(second.mSpritePathContainer);
	}
}
