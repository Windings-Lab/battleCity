#pragma once

#include "Aliases.h"

namespace BattleCity::Engine::Texture
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
