#include "PCHeader.h"
#include "Group.h"

namespace BattleCity::Texture
{
	void swap(Group& first, Group& second) noexcept
	{
		first.mPaths.swap(second.mPaths);
	}

	Group::Group(Group&& mve) noexcept : Group()
	{
		swap(*this, mve);
	}
	Group& Group::operator=(Group&& mve) noexcept
	{
		swap(*this, mve);
		return *this;
	}

	void Group::Init(const Sprite::FolderPath& spriteFolderPath)
	{
		using namespace std::filesystem;

		const path spriteFolderPathFS(spriteFolderPath);
		if (!exists(spriteFolderPathFS))
		{
			std::cerr << "Sprite Folder Path has not been found\n";
			std::cerr << "Make sure that " << spriteFolderPath << " in folder with BattleCity.exe file\n";
			throw std::invalid_argument("Can't find sprite folder");
		}

		const path fileExtension = ".png";
		for (const auto& folderEntry : recursive_directory_iterator(spriteFolderPathFS))
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

			mPaths.try_emplace(type.value(), folderEntry.path().string());
		}
	}
	const Path& Group::Get(Type spriteType) const
	{
		const auto& pathIterator = mPaths.find(spriteType);
		if (pathIterator == mPaths.end())
		{
			throw std::out_of_range("Sprite data has not been created");
		}

		return pathIterator->second;
	}

	std::optional<Type> Group::TypeFrom(const std::filesystem::path& spritePath) const
	{
		using magic_enum::enum_cast;

		const std::string typeStr = spritePath.stem().string();
		const auto& typeCast= enum_cast<Type>(typeStr);

		if (!typeCast.has_value())
		{
			std::cerr << typeStr << ": have no usage.\n";
		}

		return typeCast;
	}

	Group::PathContainer::const_iterator Group::begin() const
	{
		return mPaths.cbegin();
	}
	Group::PathContainer::const_iterator Group::end() const
	{
		return mPaths.cend();
	}

	bool Group::IsEmpty() const
	{
		return mPaths.empty();
	}

	void Group::Clear()
	{
		mPaths.clear();
	}
}
