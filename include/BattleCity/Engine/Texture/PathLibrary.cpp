#include "PCHeader.h"
#include "PathLibrary.h"

namespace BattleCity::Engine::Texture
{
	PathLibrary::PathLibrary(const std::filesystem::path& folderPath)
	{
		using namespace std::filesystem;

		if (!exists(folderPath))
		{
			std::cerr << "Folder has not been found\n";
			std::cerr << "Make sure that " << folderPath.string() << " is in place with BattleCity.exe\n";
			return;
		}

		const path fileExtension = ".png";
		for (const auto& folderEntry : recursive_directory_iterator(folderPath))
		{
			if (folderEntry.path().extension() != fileExtension)
			{
				continue;
			}

			mPaths.emplace_back(folderEntry.path().string());
		}
	}
}
