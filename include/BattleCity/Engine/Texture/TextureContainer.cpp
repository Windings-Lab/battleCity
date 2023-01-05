#include "PCHeader.h"
#include "TextureContainer.h"

#include "TexturePathLibrary.h"

namespace BattleCity::Engine::Texture
{
#ifdef _DEBUG
	namespace
	{
		void OutputAllTextures(const TextureContainer& textures)
		{
			std::cout << "Created textures: " << std::endl;

			for (const auto& texture : textures)
			{
				std::cout << texture << std::endl;
			}
			std::cout << std::endl;
		}
	}
#endif

	void swap(Container& f, Container& s) noexcept
	{
		f.mTextures.swap(s.mTextures);
	}

	void Container::CreateData(const PathLibrary& pathLibrary)
	{
		for (const auto& path : pathLibrary)
		{
			mTextures.emplace_back(path);
		}
#ifdef _DEBUG
		OutputAllTextures(mTextures);
#endif
	}
}
