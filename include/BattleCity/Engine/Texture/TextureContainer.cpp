#include "PCHeader.h"
#include "TextureContainer.h"

#include "TexturePathLibrary.h"

namespace BattleCity::Engine::Texture
{
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
	}

	void Container::Test() const
	{
		int w, h;
		const auto& texture = mTextures.at(0);
		texture.GetSize(w, h);

		std::cout << w << " " << h << std::endl;

		auto name = texture.GetName();

		int test = 4;
	}
}
