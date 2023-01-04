#include "PCHeader.h"
#include "TexturePathLibrary.h"

namespace BattleCity::Engine::Texture
{
	void PathLibrary::CreateData(const std::filesystem::path& folderPath)
	{
		using namespace std::filesystem;

		if (!exists(folderPath))
		{
			std::cerr << "Folder has not been found\n";
			std::cerr << "Make sure that " << folderPath.string() << " is in place with BattleCity.exe\n";
			return;
		}

		const path fileExtension = ".png";
		for (const auto& texturePath : recursive_directory_iterator(folderPath))
		{
			if (texturePath.path().extension() != fileExtension)
			{
				continue;
			}

			mPaths.emplace_back(texturePath);
		}
	}

	TexturePathContainer::const_iterator PathLibrary::begin() const noexcept
	{
		return mPaths.cbegin();
	}
	TexturePathContainer::const_iterator PathLibrary::end() const noexcept
	{
		return mPaths.cend();
	}
}
