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

	Container::Container(Container&& mve) noexcept : Container()
	{
		swap(*this, mve);
	}
	Container& Container::operator=(Container&& mve) noexcept
	{
		Container temp(std::move(mve));
		swap(*this, temp);
		return *this;
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

	TextureContainer::const_iterator Container::begin() const noexcept
	{
		return mTextures.cbegin();
	}
	TextureContainer::const_iterator Container::end() const noexcept
	{
		return mTextures.cend();
	}
	void Container::clear() noexcept
	{
		mTextures.clear();
	}
}
