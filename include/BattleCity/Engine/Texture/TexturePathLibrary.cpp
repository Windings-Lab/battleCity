#include "PCHeader.h"
#include "TexturePathLibrary.h"

namespace BattleCity::Engine::Texture
{
#ifdef _DEBUG
	namespace 
	{
		void OutputAllPaths(const TexturePathContainer& paths)
		{
			std::cout << "Created texture paths: " << std::endl;

			for (const auto& path : paths)
			{
				std::cout << "Path: " << path.string() << "\n";
			}
			std::cout << std::endl;
		}
	}
#endif

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

#ifdef _DEBUG
		OutputAllPaths(mPaths);
#endif
	}

	TexturePathContainer::const_iterator PathLibrary::begin() const noexcept
	{
		return mPaths.cbegin();
	}
	TexturePathContainer::const_iterator PathLibrary::end() const noexcept
	{
		return mPaths.cend();
	}
	void PathLibrary::clear() noexcept
	{
		mPaths.clear();
	}
}
