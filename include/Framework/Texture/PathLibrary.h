#pragma once

#include "Framework/Texture/Aliases.h"

namespace BattleCity::Framework::Texture
{
	class PathLibrary final
	{
	private:
		using PathContainer = std::vector<FolderPath>;

	public:
		PathLibrary(const std::filesystem::path&);

	private:
		PathContainer mPaths;

	};
}
